#include "DecisionTree.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <string>
#include <vector>
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

float entropy(std::vector<DecisionTree::value>& val, int count) {
	float result = 0;
	for (int i = 0; i < val.size(); i++)
	{
		float x = (float)val[i].count / (float)count;
		result += (-x) * log10(x);
	}

	return result;
}

void getDifferentVal(std::vector<DecisionTree::value>& val, std::vector<std::string>& data) {
	bool cpy = 1;
	DecisionTree::value buff;

	for (std::string& d : data) {
		if (val.size() == 0) {
			buff.val = d;
			val.push_back(buff);
		}

		else {
			for (DecisionTree::value& v : val) {
				if (d == v.val)
					cpy = 0;
			}
			if (cpy == 1) {
				buff.val = d;
				val.push_back(buff);
			}
			cpy = 1;
		}
	}

}

void countRows(std::vector<DecisionTree::value>& val, std::vector<std::string>& data) {
	for (std::string& d : data) {
		for (DecisionTree::value& v : val) {
			if (d == v.val)
				v.count++;
		}
	}
}

int main() {
	//test namespace CSV : works
	float start = (float)clock();
	float model = 0.0f;
	Tree::Node* root = new Tree::Node;

	CSV::File trainingData;

	//set up in needed
	trainingData.openfile("C:/Users/ageta/Desktop/DM/Project/Training Data.csv");

	model = ((float)clock() - start);
	cout << "Time to load file to memory: " << (float)( model / CLOCKS_PER_SEC) << "s" << endl;

	std::vector<int> arr;
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);
	arr.push_back(5);
	arr.push_back(6);
	arr.push_back(7);
	arr.push_back(8);
	arr.push_back(9);
	arr.push_back(10);
	arr.push_back(11);
	arr.push_back(12);
	arr.push_back(13);
	cout << "Building decision tree...";
	DecisionTree::buildTree(trainingData, arr, 0, root);
	cout << endl;
	DecisionTree::drawTree(root, -1);

	cout << "Time to build model: " << (float)(((float)clock() - model) / CLOCKS_PER_SEC) << "s" << endl;

	CSV::File testingData;
	testingData.rowCount = 43438;
	//set up in needed
	testingData.openfile("C:/Users/ageta/Desktop/DM/Project/Testing Data.csv");

	DecisionTree::testModel(testingData, root);


	cin.get();
	

}























