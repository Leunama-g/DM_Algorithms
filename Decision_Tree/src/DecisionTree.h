#pragma once
#include "UtilityFunctions.h"
#include <vector>
#include <math.h>

namespace DecisionTree {

	struct value {
		std::string val;
		int count = 0;

		int fatal = 0, serious = 0, slight = 0;

	};

	void buildTree(CSV::File& dataset, std::vector<int>& attributes, int level, Tree::Node* root);

	float entropy(std::vector<value>& val, int count);

	float entropyAttrib(int fatal, int serious, int slight, int count);

	void countRows(std::vector<value>& val, std::vector<std::string>& data);

	void getDifferentVal(std::vector<std::string>& val, std::vector<std::string>& data);

	int testRow(CSV::Row& data, Tree::Node* model);

	void testModel(CSV::File& test, Tree::Node* model);

	void drawTree(Tree::Node* root, int level);

}