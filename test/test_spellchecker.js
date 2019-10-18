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
		it('detects multiple correctly spelled words async', function(done) {
			let c = new SpellChecker();
			let words = ['table', 'tble', 'fish', 'fosj', 'apples', 'aples', 'truth', 'treth'];
			let expectedResult = [false, true, false, true, false, true, false, true];
			let promises = [];
			for(let word of words) {
				promises.push(new Promise((resolve, reject) => { 
					c.isMisspelledAsync(word, function(err, misspelled) {
						err ? reject(err) : resolve(misspelled);
					});
				}));
			}
			Promise.all(promises).then((results) => {
				assert.deepStrictEqual(results, expectedResult);
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
	});
	describe("#getCorrectionsForMisspellingAsync()", function() {
		it('describe suggestions for misspellings async', function(done) {
			let c = new SpellChecker();
			c.getCorrectionsForMisspellingAsync("pancils", function(err, suggestions) {
				assert.equal(err, undefined);
				assert.equal(suggestions.length > 5, true);
				assert.equal(suggestions.includes('pencils'), true);
				done();	
			});
		});
		it('describe multiple suggestions for misspellings async', function(done) {
			let c = new SpellChecker();
			let words = ['tble', 'bateries', 'fost', 'aples', 'treth'];
			let corrections = ['table', 'batteries', 'fast', 'apples', 'truth']
			let promises = [];
			for(let word of words) {
				promises.push(new Promise((resolve, reject) => { 
					c.getCorrectionsForMisspellingAsync(word, (err, misspelled) => {
						err ? reject(err) : resolve(misspelled);
					});
				}));
			}
			Promise.all(promises).then((results) => {
				for(var i = 0; i < corrections.length; i++) {
					assert.equal(results[i].includes(corrections[i]), true);
				}
				done();
			});
		});
	});
});
