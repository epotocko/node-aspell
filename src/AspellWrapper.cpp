#include <stdexcept>
#include "AspellWrapper.h"

// Initialize aspell objects
AspellWrapper::AspellWrapper(std::string lang) {
	this->aspellConfig = new_aspell_config();
	if(lang.length() > 0) {
		aspell_config_replace(this->aspellConfig, "lang", lang.c_str());
	}
	AspellCanHaveError* possibleError = new_aspell_speller(this->aspellConfig);
	if (aspell_error_number(possibleError) != 0) {
		throw std::runtime_error(aspell_error_message(possibleError));
	}
	else {
		this->spellChecker = to_aspell_speller(possibleError);
	}
}

// Free memory used by aspell
AspellWrapper::~AspellWrapper() {
	delete_aspell_speller(this->spellChecker);
	delete_aspell_config(this->aspellConfig);
}

// Returns true if the word is misspelled
bool AspellWrapper::isMisspelled(const std::string word) {
	return aspell_speller_check(this->spellChecker, word.c_str(), -1) != 1;
}

// Returns a list of suggestions for a misspelled word
std::vector<std::string> AspellWrapper::getCorrectionsForMisspelling(const std::string word) {
	const AspellWordList* suggestions = aspell_speller_suggest(this->spellChecker, word.c_str(), -1);
	AspellStringEnumeration* elements = aspell_word_list_elements(suggestions);
	const char* suggestion;
	std::vector<std::string> results;
	while((suggestion = aspell_string_enumeration_next(elements)) != NULL) {
		results.push_back(std::string(suggestion));
	}	
	delete_aspell_string_enumeration(elements);
	return results;
}