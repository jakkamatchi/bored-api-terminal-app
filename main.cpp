#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Node.h"
#include "JSONFile.h"

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

int main(int argc, char** argv) {
	//ToDo:
	
	if(argc != 2) { return 1; }

	std::stringstream RawJSONFile;			
	
	RawJSONFile = RetrieveData(argv[1]);			
	std::vector<std::string> TokenisedJSON = TokeniseJSON(RawJSONFile.str());

	JSONFile ParsedFile(TokenisedJSON);
	ParsedFile.Print();

	std::shared_ptr<Node> BaseNode = ParsedFile.PrimaryNode;
	BaseNode = (*BaseNode)["OBJECT_NODE_0"];

	std::shared_ptr<Node> ActivityNode = (*BaseNode)["activity"];
	ActivityNode = ActivityNode->ChildNodes[0];	

	std::shared_ptr<Node> TypeNode =(*BaseNode)["type"];
	TypeNode = TypeNode->ChildNodes[0];
	
	std::shared_ptr<Node> ParticipantsNode = (*BaseNode)["participants"];
	ParticipantsNode = ParticipantsNode->ChildNodes[0];

	const std::string BOLD_ON = "\033[1m";	
	const std::string BOLD_OFF = "\033[21m";
	
	const std::string UNDERLINE_ON = "\033[4m";	
	const std::string UNDERLINE_OFF = "\033[24m";
	
	const std::string RESET_COLOUR = "\033[49m";	
	const std::string BLUE= "\033[48;5;27m";
	const std::string RED = "\033[48;5;162m";
	const std::string GREEN = "\033[48;5;64m";

	std::cout << std::endl << BOLD_ON << UNDERLINE_ON << "Fun Stuff !" << std::endl << std::endl;
	
	std::cout << BOLD_OFF << UNDERLINE_OFF;
	std::cout << RESET_COLOUR;
	
	std::cout << BLUE << "Activity: " << ActivityNode->GetData() << RESET_COLOUR << "\n";
	std::cout << GREEN << "Type: " << TypeNode->GetData() << RESET_COLOUR << "\n";	

	std::cout << RED << "Participants: " << ParticipantsNode->GetData() << RESET_COLOUR << "\n";

	std::cout << std::endl;
	return 0;
}

