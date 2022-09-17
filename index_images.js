const Jimp = require('jimp');
const _ = require('lodash');
const path = require('path');


const Rotate = {
  '_0': 0,      // no adjustment
  '_90': 90,    // rotate 90 degrees clockwise
  '_180': 180,  // rotate 180 degrees clockwise
  '_270': 270   // rotate 270 degrees clockwise
}
// file to read. Make sure the path is good
const images = [
  './assets/balloons.jpg',
  './assets/rainbow.png',
  './assets/stripes.png',
  './assets/sunset.png',
];

const settings = {
  pixels: 30,       // how many neopixels in the group?
  fps: 5,           // how many frames per second?
  rotate: Rotate._0,
}

function getMatte(width, height) {
  return new Promise((resolve, reject) => {
    new Jimp(width, height, 0xff000000, (err, image) => {
      if (err) reject(err);
      resolve(image);
    });
  });
}

function strigifyArrayForCcode(input) {
  var expanded = JSON.stringify(input);
  expanded = expanded.replace(/\[/g, '{');
  expanded = expanded.replace(/\]/g, '}');
  expanded = expanded.replace(/\"/g, '');
  return expanded;
}

function expand(data, template) {
  const expanded = strigifyArrayForCcode(data);
  console.log(template({ data: expanded, count: data.length }));
}

// turn image files into indexed pallet maps
let imageData = images.map(function (subject, index) {
  return Jimp.read(subject)
    .then(img => {
      const prepared = img
        .rotate(settings.rotate)
        .resize(settings.pixels, Jimp.AUTO, Jimp.RESIZE_BILINEAR)

      return getMatte(img.bitmap.width, img.bitmap.height)
        .then(matte => {
          // blend alpha channel to matte
          return matte.composite(img, 0, 0, {
            mode: Jimp.BLEND_SOURCE_OVER,
            opacitySource: 1,
            opacityDest: 1,
          });
        });
    })
    .then(flat => {
      let ext = path.extname(subject);
      let base = path.basename(subject, ext);
      let destination = path.resolve(__dirname, 'preview', `${base}.png`);

      flat.write(destination); // save

      let pallette = [];
      let rows = [];

      for (var i = 0; i < flat.bitmap.height; i++) {
        // scan 1 row at a time
        const row = [];
        flat.scan(0, i, flat.bitmap.width, 1, function (x, y, idx) {

          var red = flat.bitmap.data[idx + 0];
          var green = flat.bitmap.data[idx + 1];
          var blue = flat.bitmap.data[idx + 2];

          const hexVal = '0x' + [
            red.toString(16).padStart(2, '0'),
            green.toString(16).padStart(2, '0'),
            blue.toString(16).padStart(2, '0')
          ].join('').toUpperCase();

          var found = pallette.findIndex((item) => item == hexVal);

          if (found > -1) {
            // this is the index of our indexed color
            row.push(found);
          } else {
            row.push(pallette.length);
            pallette.push(hexVal);
          }

        });

        rows.push(row);
      }

      return {
        pallette: pallette,
        rows: rows
      }
    }).catch(err => {
      console.error(err);
    });

});


console.log('finished processing pass 1');
Promise.allSettled(imageData).then((data)=>{
  let combinedPallette = [];
  let images = data.map(item=>item.value);

  let indexDataOnly = images.map(item=>{
    return item.rows.map(row=>{
      return row.map(pixel=>{
        var localColor = item.pallette[pixel];
        var found = combinedPallette.findIndex((item) => item == localColor);

        if (found > -1) {
          // this is the index of our indexed color
          return found;
        } else {
          let position = combinedPallette.length;
          combinedPallette.push(localColor);
          return position;
        }
      })
    })
  });

  console.log('combinedPallette', combinedPallette.length);
  console.log('indexDataOnly', indexDataOnly);

});