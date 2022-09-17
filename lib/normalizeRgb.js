const hexEvens = {
  '0':  '0',
  '1':  '0',
  '2':  '2',
  '3':  '2',
  '4':  '4',
  '5':  '4',
  '6':  '6',
  '7':  '6',
  '8':  '8',
  '9':  '8',
  'a':  'a',
  'b':  'a',
  'c':  'c',
  'd':  'c',
  'e':  'e',
  'f':  'e',
}

const hexQuads = {
  '0': '3',
  '1': '3',
  '2': '3',
  '3': '3',
  '4': '7',
  '5': '7',
  '6': '7',
  '7': '7',
  '8': 'b',
  '9': 'b',
  'a': 'b',
  'b': 'b',
  'c': 'f',
  'd': 'f',
  'e': 'f',
  'f': 'f',
}

function roundHex(hexString) {
  return hexString;
}

module.exports = {
  roundHex
}