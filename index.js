var Jimp = require('jimp');

const Rotate = {
  '_0': 0,      // no adjustment
  '_90': 90,    // rotate 90 degrees clockwise
  '_180': 180,  // rotate 180 degrees clockwise
  '_270': 270   // rotate 270 degrees clockwise
}

const subject = './assets/stripes.png'; // file to read. Make sure the path is good
const settings = {
  pixels: 20,       // how many neopixels in the group?
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

Jimp.read(subject)
  .then(img => {
    const prepared = img
      .rotate(settings.rotate)
      .resize(settings.pixels, Jimp.AUTO, Jimp.RESIZE_BILINEAR);


      getMatte(img.bitmap.width, img.bitmap.height).then(matte=>{
        // blend alpha channel to matte
        const flat = matte.composite(img, 0, 0, {
          mode: Jimp.BLEND_SOURCE_OVER,
          opacitySource: 1,
          opacityDest: 1,
        });

        flat.write('newFirePhoto_preview.jpg'); // save


        var output_head = `uint8_t sequence[${flat.bitmap.height}][${flat.bitmap.width * 3}]`
        var rows = [];

        for(var i = 0; i < flat.bitmap.height; i++) {
          // scan 1 row at a time
          rows.push([]);
          img.scan(0, i, flat.bitmap.width, 1, function(x, y, idx) {
            var red = flat.bitmap.data[idx + 0];
            var green = flat.bitmap.data[idx + 1];
            var blue = flat.bitmap.data[idx + 2];

            const hexVal = [
              red.toString(16).padStart(2, '0'),
              green.toString(16).padStart(2, '0'),
              blue.toString(16).padStart(2, '0')
            ].join('').toUpperCase();

            rows[i].push(red)
            rows[i].push(green)
            rows[i].push(blue)
            // rows[i].push([red, green, blue]);
          });

          
        }

        var expanded = JSON.stringify(rows);
        expanded = expanded.replace(/\[/g, '{');
        expanded = expanded.replace(/\]/g, '}');
        expanded = expanded.replace(/\"/g, '');

        console.log(' ');
        console.log(' ');
        console.log(' ');
        console.log(`//========${subject}======== - generated ${Date.now()}`);
        console.log(' ');
        console.log(`uint8_t seq_width = ${flat.bitmap.width}; // width of image sequence data`);
        console.log(`uint8_t seq_height = ${flat.bitmap.height}; // width of image sequence data`);
        console.log(`uint8_t seq_delay = ${Math.round(1000/settings.fps)}; // delay in ms`);
        console.log(' ');
        console.log(output_head + '=' + expanded + ';');
      });
      
    
    
      
      // .write('lena-small-bw.jpg'); // save
  })
  .catch(err => {
    console.error(err);
  });