const aspell = require('./build/Release/aspell.node');
const SpellChecker = aspell.SpellChecker;

// Following API of https://github.com/atom/node-spellchecker
const defaultSpellChecker = new SpellChecker();
defaultSpellChecker.Spellchecker = SpellChecker;
module.exports = defaultSpellChecker;
