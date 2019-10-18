#include "SpellChecker.h"
#include "IsMisspelledWorker.h"
#include "SuggestionsWorker.h"

Napi::FunctionReference SpellChecker::constructor;

Napi::Object SpellChecker::Init(Napi::Env env, Napi::Object exports) {
	Napi::HandleScope scope(env);

	// Setup SpellChecker class definition
	Napi::Function func = DefineClass(env, "SpellChecker", {
		InstanceMethod("isMisspelled", &SpellChecker::isMisspelled),
		InstanceMethod("isMisspelledAsync", &SpellChecker::isMisspelledAsync),
		InstanceMethod("getCorrectionsForMisspelling", &SpellChecker::getCorrectionsForMisspelling),
		InstanceMethod("getCorrectionsForMisspellingAsync", &SpellChecker::getCorrectionsForMisspellingAsync)
	});

	constructor = Napi::Persistent(func);
	constructor.SuppressDestruct();

	exports.Set("SpellChecker", func);
	return exports;
}

SpellChecker::SpellChecker(const Napi::CallbackInfo& info) : Napi::ObjectWrap<SpellChecker>(info)  {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	try {
		if(info.Length() > 0) {
			if(!info[0].IsString()) {
				Napi::TypeError::New(env, "Expected string for language argument").ThrowAsJavaScriptException();
			}
			std::string language = info[0].As<Napi::String>();
			this->aspell = new AspellWrapper(language);
		}
		else {
			this->aspell = new AspellWrapper();
		}
	}
	catch(std::runtime_error& e) {
		Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
	}
}

SpellChecker::~SpellChecker() {
	if(this->aspell != NULL) {
		delete this->aspell;
	}
}

Napi::Value SpellChecker::isMisspelled(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	std::string word = info[0].As<Napi::String>();
	return Napi::Boolean::New(env, this->aspell->isMisspelled(word));
}

Napi::Value SpellChecker::isMisspelledAsync(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	std::string word = info[0].As<Napi::String>();
	Napi::Function callback = info[1].As<Napi::Function>();
	IsMisspelledWorker* worker = new IsMisspelledWorker(callback, this->aspell, word);
	worker->Queue();
	return env.Undefined();
}

Napi::Value SpellChecker::getCorrectionsForMisspelling(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	std::string word = info[0].As<Napi::String>();
	std::vector<std::string> suggestions = this->aspell->getCorrectionsForMisspelling(word);

	// Convert vector to Napi::Array
	Napi::Array results = Napi::Array::New(env, suggestions.size());
	int i = 0;
	for(auto iter = suggestions.begin(); iter != suggestions.end(); ++iter) {
		results[i++] = Napi::String::New(env, *iter);
	}

	return results;
}

Napi::Value SpellChecker::getCorrectionsForMisspellingAsync(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	std::string word = info[0].As<Napi::String>();
	Napi::Function callback = info[1].As<Napi::Function>();
	SuggestionsWorker* worker = new SuggestionsWorker(callback, this->aspell, word);
	worker->Queue();
	return env.Undefined();
}

