#pragma once
#include <fstream>
#include <string>
#include <vector>

namespace CSV 
{

	struct Row {
		std::string accidentSeverity;
		std::string noOfVehicles;
		std::string noOfCasualties;
		std::string dayOfWeek;
		std::string time;
		std::string roadType;
		std::string speedLimit;
		std::string junctionDetail;
		std::string junctionControl;
		std::string pedCrossHuman;
		std::string pedControlPhysical;
		std::string lightCondition;
		std::string urbanOrRural;
	};

	class File
	{
		public:
			int rowCount = 28962; //479917
			void returnnCol(int id, std::vector<std::string>& outCol);
			Row returnRow(int id);
			std::vector<Row> dataset;
			void add(Row data);
			File();
			void openfile(const char* filePath);
			~File();
		private:
			std::string readTillComma();
			std::ifstream file;
			std::string line;
			void readfile(); //done
	};
}

namespace Tree {

	class Node {
	public:
		int colID;
		std::string val = "";
		int fatal = 0, serious = 0, slight = 0;
		std::vector<Node*> children;
		void add_child(Node* child);
		//does not have a destructor yet... probably dont need it... small app... project deadline soon ...lol
	};

}

