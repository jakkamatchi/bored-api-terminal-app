#ifndef __JSONFILE_H_INCLUDED__
#define __JSONFILE_H_INCLUDED__

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "Node.h"

class JSONFile {
	public:
		JSONFile(std::vector<std::string >);
		~JSONFile();

		std::shared_ptr<Node> PrimaryNode;

		std::shared_ptr<Node> operator[](std::string);

		void Print();
};

#endif
