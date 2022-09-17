const chai = require('chai');
const normalize = require('../lib/normalizeRgb');
var expect = chai.expect;

const colors = {
  middleGray: '0x888888'
}



describe('Normalize RBG', function () {
  describe('roundHex', function () {
    it('should return medium gray untouched as 8 bit color byte', function () {
      expect(normalize.roundHex(colors.middleGray)).to.equal(colors.middleGray);
    });
  });
});