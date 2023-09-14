# aspell Node Module

Native bindings to [aspell](http://aspell.net/) spell checking library for Node.js.

## Installation
```bash
npm install node-aspell
```

## Usage

```javascript
const spellChecker = require('node-aspell');
console.log(spellChecker.isMisspelled("pncils"));
console.log(spellChecker.getCorrectionsForMisspelling("pncils"));
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

### new Spellchecker(options)

In addition to the above functions that are used on a default instance, a new instance of SpellChecker can be instantiated with the use of the `new` operator. The same methods are available with the instance but the language/dictionary can be changed independently from the default instance. See the aspell options documentation for a full list of options: http://aspell.net/man-html/The-Options.html

```javascript
const checker = new SpellChecker.Spellchecker({ lang: "es", encoding: "utf-8" });
const checker = new SpellChecker.Spellchecker({
	'master': 'es.rws',
	'dict-dir': '/var/lib/aspell',
	'encoding': 'utf-8'
});
const checker = new SpellChecker.Spellchecker("en_US");
```

## Unit Tests

Sample Dockerfile for running unit tests:
```
FROM node:xx
RUN apt-get update && apt-get install -y aspell aspell-en aspell-es libaspell-dev
COPY . /module
WORKDIR /module
RUN npm install && npm run-script build
RUN npm test
```

## Alternatives
These packages spawn a separate aspell process and parse the output:

[aspell](https://www.npmjs.com/package/aspell)

[aspell-stream](https://www.npmjs.com/package/aspell-stream)

