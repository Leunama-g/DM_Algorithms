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
			int rowCount = 15; //479917
			void returnnCol(int id, std::string* outCol);
			Row returnRow(int id);
			File(const char* filePath);
			~File();
		private:
			std::string readTillComma();
			std::ifstream file;
			Row* dataset;
			std::string line;
			void readfile(); //done
	};
}

namespace Tree {

	class node {
	public:
		int id;
		std::string info;
		node* parent;
		/*std:::vector<node*> children;

		node(node* parent) : parent(parent)
		{
		}

		void add_child(node* child) { children.push_back(child); }*/
	};

}