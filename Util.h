#ifndef __UTIL_H_INCLUDED__
#define __UTIL_H_INCLUDED__

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> TokeniseJSON(std::string Input) {
	std::vector<std::string > TokenList;
	int SubstringIndex = 0;
	int SubstringLength = 1;
	std::string Substring = "";

	bool isString = false;

	for(int i = 0; i < Input.size(); i++) {
		if (Input[i] == '"') {
			isString = !isString;
			SubstringLength++;
		}

		else if (Input[i] == ' '  && !isString) {
			Input.erase(i, 1);
			i = i - 1;
		}

		else if (Input[i] == '\n') {
			Input.erase(i, 1);
			i = i - 1;
		}
		else if(	(Input[i] == '{' ||
				Input[i] == '}' ||
				Input[i] == ',' ||
				Input[i] == '[' ||
				Input[i] == ']' ||
		       		Input[i] == ':') && isString == false)	{
			
			Substring = Input.substr(SubstringIndex, SubstringLength - 1);
			
			if(Substring.empty() == false) {	
				TokenList.push_back(Substring);
			}

			Substring = Input.substr(i, 1);
			if(Substring.empty() == false) {
				TokenList.push_back(Substring);
			}
			
			SubstringIndex = i + 1 ;
			SubstringLength = 1;
		}
		else {
			SubstringLength++;
		}
	}

	for(int i = 0; i < TokenList.size(); i++) {
		if(TokenList[i][0] == '"' && TokenList[i][TokenList[i].size() - 1] == '"') {
			TokenList[i].erase(0, 1);
			TokenList[i].erase(TokenList[i].size() - 1, 1);
		}
	}

	return TokenList;	
}

std::stringstream RetrieveData(char* Input) {
	std::stringstream raw;

	try {
		curlpp::Cleanup myCleanup;
		curlpp::Easy myRequest;
		myRequest.setOpt<curlpp::options::Url>(Input);
		raw << myRequest;
		return raw;
	}
	catch(curlpp::RuntimeError& e) {
		std::cout << e.what();
	}

	catch(curlpp::LogicError& e) {
		std::cout << e.what();
	}
}

#endif
