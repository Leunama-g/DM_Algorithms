#include <iostream>
#include "UtilityFunctions.h"


namespace CSV {

	File::File() {
		
	}

	File::~File() {
		//delete dataset from memory
		dataset.clear();
	}

	void File::openfile(const char* filePath) {
		//open file
		file.open(filePath, std::ios::in);

		//dataset = new Row[15]; //500000

		//get dataset values from file and load them to memory
		readfile();
	}

	std::string File::readTillComma() {

		std::string data = "";
		char key;

		key = line[0];

		for (int i = 1; i < line.length(); i++) {
			if (key != ',') {
				data += key;
			}
			else
				break;
			key = line[i];
		}
		line = line.substr((data.length() + 1), line.length());
		return data;
	}

	void File::readfile() {
		Row buffer;

		//to skip the attribute names
		std::getline(file, line);

		for (int i = 0; i < rowCount; i++){
			//read row
			std::getline(file, line);

			buffer.accidentSeverity = readTillComma();
			buffer.noOfVehicles = readTillComma();
			buffer.noOfCasualties = readTillComma();
			buffer.dayOfWeek =readTillComma();
			buffer.time = readTillComma().c_str();
			buffer.roadType = readTillComma();
			buffer.speedLimit = readTillComma().c_str();
			buffer.junctionDetail = readTillComma();
			buffer.junctionControl = readTillComma();
			buffer.pedCrossHuman = readTillComma();
			buffer.pedControlPhysical = readTillComma();
			buffer.lightCondition = readTillComma();
			buffer.urbanOrRural = readTillComma();

			dataset.push_back(buffer);
		}
	}

	void File::add(Row data) {
		dataset.push_back(data);
	}

	Row File::returnRow(int id) {
		return dataset[id];
	}

	void File::returnnCol(int id, std::vector<std::string>& outCol) {
		switch (id)
		{
		case 1:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].accidentSeverity);
			}
			break;
		case 2:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].noOfVehicles);
			}
			break;
		case 3:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].noOfCasualties);
			}
			break;
		case 4:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].dayOfWeek);
			}
			break;
		case 5:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].time);
			}
			break;
		case 6:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].roadType);
			}
			break;
		case 7:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].speedLimit);
			}
			break;
		case 8:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].junctionDetail);
			}
			break;
		case 9:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].junctionControl);
			}
			break;
		case 10:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].pedCrossHuman);
			}
			break;
		case 11:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].pedControlPhysical);
			}
			break;
		case 12:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].lightCondition);
			}
			break;
		case 13:
			for (int i = 0; i < rowCount; i++) {
				outCol.push_back(dataset[i].urbanOrRural);
			}
			break;
		default:
			break;
		}
	}
}

namespace Tree {

	void Node::add_child(Node* child) 
	{
		children.push_back(child); 
	}
}

