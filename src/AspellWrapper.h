#include <aspell.h>
#include <string>
#include <vector>
#pragma once

// Wrapper around aspell C API to map types to std library types
// http://aspell.net/man-html/Through-the-C-API.html
class AspellWrapper {

	private:
		AspellConfig* aspellConfig;
		AspellSpeller* spellChecker;

	public:
		AspellWrapper(std::string lang = "");
		~AspellWrapper();
		bool isMisspelled(const std::string);
		std::vector<std::string> getCorrectionsForMisspelling(const std::string);

};