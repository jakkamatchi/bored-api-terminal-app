#include "Node.h"

#include <string>
#include <iostream>

void Node::SetKey(std::string _data) {
	DataField = _data;
}

std::string Node::GetData() {
	return DataField;
}

void Node::SetParentNode(std::shared_ptr<Node> _node) {
	ParentNode = _node;
}


void Node::AddChildNode(std::shared_ptr<Node> _node) {
	ChildNodes.push_back(_node);
}

void Node::Print() {
	std::cout << "Field " << DataField << " contains " << ChildNodes.size() << " child nodes:";
	
	for(int i = 0; i < ChildNodes.size(); i++) {
		std::cout << i << ") " << ChildNodes[i]->DataField << " ";
	}
	
	std::cout << std::endl;

	for(int i = 0; i < ChildNodes.size(); i++) {
		ChildNodes[i]->Print();
	}
}

std::shared_ptr<Node> Node::GetParentNode() {
	return ParentNode;
}

std::shared_ptr<Node> Node::GetSubNodeByID(std::string _parameter) {
	for(int i = 0; i < this->ChildNodes.size(); i++) {
		
		if(this->ChildNodes[i]->DataField == _parameter) {
			return this->ChildNodes[i];	
		};
	}

	return nullptr;
}

std::shared_ptr<Node> Node::operator[](std::string _param) {
	return GetSubNodeByID(_param);
};
