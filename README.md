# aspell Node Module

Native bindings to [aspell](http://aspell.net/) for Node.js.

## Usage

```javascript
const spellChecker = require('node-aspell');
console.log(spellChecker.isMisspelled("pncils"));
```

### spellChecker.isMisspelled(word)

Check if a word is misspelled.

`word` - String word to check.

Returns `true` if the word is misspelled, `false` otherwise.

### spellChecker.isMisspelledAsync(word, callback)

Check if a word is misspelled asynchronously.

`word` - String word to check.

`callback` - Function to call with result callback(err, misspelled)

### spellChecker.getCorrectionsForMisspelling(word)

Get the corrections for a misspelled word.

`word` - String word to get corrections for.

Returns a non-null but possibly empty array of string corrections.

### spellChecker.getCorrectionsForMisspellingAsync(word, callback)

Get the corrections for a misspelled word asynchronously.

`word` - String word to get corrections for.

`callback` - Function to call with result

### new Spellchecker(language)

In addition to the above functions that are used on a default instance, a new instance of SpellChecker can be instantiated with the use of the `new` operator. The same methods are available with the instance but the language can be changed independently from the default instance.

```javascript
const checker = new SpellChecker.Spellchecker("en_US");
```
