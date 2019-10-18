const assert = require('assert');
const SpellChecker = require('../index.js').Spellchecker;

describe('SpellChecker', function() {
	describe('#isMisspelled()', function() {
		it('detects correctly spelled words', function() {
			let c = new SpellChecker();
			assert.equal(c.isMisspelled('baseball'), false);
			assert.equal(c.isMisspelled('beseball'), true);
			assert.equal(c.isMisspelled('pencils'), false);
			assert.equal(c.isMisspelled('pncils'), true);
		});
	});
	describe('#isMisspelledAsync()', function() {
		it('detects correctly spelled words', function(done) {
			let c = new SpellChecker();
			c.isMisspelledAsync('baseball', function(err, correct) {
				assert.equal(correct, false);
				done();
			});
		});
	});
	describe("#getCorrectionsForMisspelling()", function() {
		it('describe suggestions for misspellings', function() {
			let c = new SpellChecker();
			let suggestions = c.getCorrectionsForMisspelling("pancils");
			assert.equal(suggestions.length > 5, true);
			assert.equal(suggestions.includes('pencils'), true);
		});
	})
});
