#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

#include <vector>
#include <string>
#include <memory>

class Node {
	public:
		Node (std::string _data) : DataField(_data) { };
		~Node () { };
	
		std::string DataField;

		void SetKey(std::string);
		std::string GetData();

		std::shared_ptr<Node> ParentNode;
		std::vector<std::shared_ptr<Node> > ChildNodes;
		
		std::shared_ptr<Node>  GetParentNode();

		void SetParentNode(std::shared_ptr<Node>);
		void AddChildNode(std::shared_ptr<Node>);
		
		std::shared_ptr<Node> GetSubNodeByID(std::string);
		
		std::shared_ptr<Node> operator[](std::string);

		void Print();
};

#endif
