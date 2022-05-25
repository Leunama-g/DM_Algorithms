#include <iostream>
#include "UtilityFunctions.h"

namespace CSV {

	File::File(const char* filePath) {
		//open file
		file.open(filePath, std::ios::in);

		dataset = new Row[15]; //500000

		//get dataset values from file and load them to memory
		readfile();
	}

	File::~File() {
		//delete dataset from memory
		delete[] dataset;
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

		//to skip the attribute names
		std::getline(file, line);

		for (int i = 0; i < rowCount; i++){
			//read row
			std::getline(file, line);

			dataset[i].accidentSeverity = readTillComma();
			dataset[i].noOfVehicles = readTillComma();
			dataset[i].noOfCasualties = readTillComma();
			dataset[i].dayOfWeek =readTillComma();
			dataset[i].time = readTillComma().c_str();
			dataset[i].roadType = readTillComma();
			dataset[i].speedLimit = readTillComma().c_str();
			dataset[i].junctionDetail = readTillComma();
			dataset[i].junctionControl = readTillComma();
			dataset[i].pedCrossHuman = readTillComma();
			dataset[i].pedControlPhysical = readTillComma();
			dataset[i].lightCondition = readTillComma();
			dataset[i].urbanOrRural = readTillComma();
		}
	}

	Row File::returnRow(int id) {
		return dataset[id];
	}

	void File::returnnCol(int id, std::string* outCol) {
		switch (id)
		{
		case 1:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].accidentSeverity;
			}
			break;
		case 2:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].noOfVehicles;
			}
			break;
		case 3:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].noOfCasualties;
			}
			break;
		case 4:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].dayOfWeek;
			}
			break;
		case 5:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].time;
			}
			break;
		case 6:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].roadType;
			}
			break;
		case 7:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].speedLimit;
			}
			break;
		case 8:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].junctionDetail;
			}
			break;
		case 9:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].junctionControl;
			}
			break;
		case 10:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].pedCrossHuman;
			}
			break;
		case 11:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].pedControlPhysical;
			}
			break;
		case 12:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].lightCondition;
			}
			break;
		case 13:
			for (int i = 0; i < rowCount; i++) {
				outCol[i] = dataset[i].urbanOrRural;
			}
			break;
		default:
			break;
		}
	}
}

