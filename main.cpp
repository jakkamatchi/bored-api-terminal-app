#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Util.h"
#include "Node.h"
#include "JSONFile.h"

int main(int argc, char** argv) {
	//ToDo:
	
	std::stringstream RawJSONFile;			

	char* URL = "https://www.boredapi.com/api/activity";
	
	//Included in Util.h	
	RawJSONFile = RetrieveData(URL);			
	std::vector<std::string> TokenisedJSON = TokeniseJSON(RawJSONFile.str());

	JSONFile ParsedFile(TokenisedJSON);
	ParsedFile.Print();

	//Set BaseNode. Can access subnodes by [] operator.
	//Failure will segfault as nullptr returned in case of no match
	std::shared_ptr<Node> BaseNode = ParsedFile.PrimaryNode;
	BaseNode = (*BaseNode)["OBJECT_NODE_0"];

	std::shared_ptr<Node> ActivityNode = (*BaseNode)["activity"];
	ActivityNode = ActivityNode->ChildNodes[0];	

	std::shared_ptr<Node> TypeNode =(*BaseNode)["type"];
	TypeNode = TypeNode->ChildNodes[0];
	
	std::shared_ptr<Node> ParticipantsNode = (*BaseNode)["participants"];
	ParticipantsNode = ParticipantsNode->ChildNodes[0];

	//Colour constants for style
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

	//Data called by GetDataMethod. Returns key value.	
	std::cout << BLUE << "Activity: " << ActivityNode->GetData() << RESET_COLOUR << "\n";
	std::cout << GREEN << "Type: " << TypeNode->GetData() << RESET_COLOUR << "\n";	

	std::cout << RED << "Participants: " << ParticipantsNode->GetData() << RESET_COLOUR << "\n";

	std::cout << std::endl;
	return 0;
}

