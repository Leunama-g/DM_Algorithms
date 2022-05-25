#include "KNN.h"
#include "DecisionTree.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <string>

#include <math.h>

#include <chrono>

using namespace std;

std::ifstream file;
string line;

string readTillComma() {

	string data = "";
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

void copyToChar(char* outStr, string data) {
	int count = data.length();

	for (int i = 0; i < count; i++) {
		outStr[i] = data[0];
	}
	
}

float entropy(int* val, int size, int count) {
	float result = 0;
	for (int i = 0; i < size; i++)
	{
		float x = (float)val[i] / (float)count;
		result += (-x) * log10(x);
	}

	return result;
}

void countRow();

int main() {
	
	//test namespace CSV : works
	/*
	float start = (float)clock();

	CSV::File test("C:/Users/ageta/Desktop/DM/Project/Test Dataset.csv");

	cout << "Time to load file to memory: " << (float)(((float)clock() - start) / CLOCKS_PER_SEC) << "s" << endl;

	CSV::Row xtest;
	
	xtest = test.returnRow(4);
	cout << xtest.accidentSeverity << ", " << xtest.dayOfWeek << ", " << xtest.junctionDetail << ", " << xtest.speedLimit  << ", " << xtest.time << endl <<endl;
	
	string* ytest = new string[500000];

	test.returnnCol(1, ytest);

	for (int i = 0; i < 15; i++)
	{
		cout << ytest[i] << endl;
	}

	delete[] ytest;
	*/

	//test namespace utilityfunctions : 

	int x[] = { 9,5 };

	cout << entropy(x,2,14);

	cin.get();
	

}