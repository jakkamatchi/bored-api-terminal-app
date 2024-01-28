#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "JSONFile.h"
#include "Node.h"

JSONFile::JSONFile (std::vector<std::string > Input) {
	PrimaryNode = std::shared_ptr<Node>(new Node("ROOT_NODE"));

	int DataType = 0;
	int Depth = -1;
	int CurrentFirstTierElement = 0;

	std::string Element;

	std::shared_ptr<Node> CurrentWorkingNode = nullptr;
	CurrentWorkingNode = PrimaryNode;

	bool CurrentArray = false;

	int CurrentObjectID = 0;

	for(int i = 0; i < Input.size(); i++) {		
		Element = Input[i];
		std::cout << "Token " << i << ": <" << Element << ">\n";
		
		//If {, then start of section. Depth can be incremented
		if(Element == "{" && Input[i - 1] != ":") {
			Depth++;
			
			std::string ObjectLabel= "OBJECT_NODE_" + std::to_string(CurrentObjectID);	
			std::shared_ptr<Node> NewNode = std::shared_ptr<Node>(new Node(ObjectLabel));
			CurrentObjectID++;

			NewNode->SetParentNode(CurrentWorkingNode);
			CurrentWorkingNode->AddChildNode(NewNode);
			CurrentWorkingNode = NewNode;
		}	
		
		//If }, then end of section. Depth can be decreased and current
		//working node incremented
		else if(Element == "}") {
			Depth--;
			CurrentWorkingNode = CurrentWorkingNode->GetParentNode();
		}

		else if(Element == "[") {
			std::shared_ptr<Node> NewNode = std::shared_ptr<Node>(new Node("ARRAY_NODE"));
			CurrentArray = true;

			NewNode->SetParentNode(CurrentWorkingNode);
			CurrentWorkingNode->AddChildNode(NewNode);
			CurrentWorkingNode = NewNode;
		}
		
		//If closiong an array, create a new working node with ID of next field
		else if(Element == "]") {
			CurrentArray = false;

			CurrentWorkingNode = CurrentWorkingNode->GetParentNode();
		}
	
		//Current element is a string, hence this and i + 2 are string pairs
		//Can create parent and child node without increasing depth
		else if(Element == ":") {

			//If {, then depth further decreases and last added node
			//becomes current parent node
			if(Input[i + 1]  == "{") {
				Depth++;
				
				std::shared_ptr<Node> NewNode = std::shared_ptr<Node>(new Node(Input[i - 1]));
				NewNode->SetParentNode(CurrentWorkingNode);
				CurrentWorkingNode->AddChildNode(NewNode);
				
				CurrentWorkingNode = NewNode;
			}

			//If [, depth can remain the same however all nodes from now on
			//are attached to parent 
			else if (Input[i + 1]  =="[") {
				i++;
			}

			//Else, it is a string and can form a new node for current
			//parent
			else {
				std::shared_ptr<Node> Parent = std::shared_ptr<Node>(new Node(Input[i - 1]));
				std::shared_ptr<Node> Child = std::shared_ptr<Node>(new Node(Input[i + 1]));
				Parent->AddChildNode(Child);
				Child->SetParentNode(Parent);
			
				CurrentWorkingNode->AddChildNode(Parent);
				Parent->SetParentNode(CurrentWorkingNode);	
			}
		}

		//Current element is comma, indicating that next dataset is
		//of same depth
	}
}

JSONFile::~JSONFile () {

}

void JSONFile::Print() {
	std::cout << std::endl;
	PrimaryNode->Print();
}

std::shared_ptr<Node> JSONFile::operator[](std::string _parameter) {	
	return PrimaryNode->GetSubNodeByID(_parameter);
}
