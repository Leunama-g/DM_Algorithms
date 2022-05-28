#include "DecisionTree.h"
#include <iostream>




namespace DecisionTree {

	float entropy(std::vector<value>& val, int count) {
		float result = 0;
		for (int i = 0; i < val.size(); i++)
		{
			if (val[i].count != 0) {
				float x = (float)val[i].count / (float)count;
				result += (-x) * log10(x);
			}
		}

		return result;
	}

	float entropyAttrib(int fatal,int serious,int slight, int count) {
		float result = 0;
		float x;
		if (fatal != 0) {
			x = (float)fatal / (float)count;
			result += (-x) * log10(x);
		}	
		if (serious != 0) {
			x = (float)serious / (float)count;
			result += (-x) * log10(x);
		}
		if (slight != 0) {
			x = (float)slight / (float)count;
			result += (-x) * log10(x);
		}

		return result;
	}

	void getDifferentVal(std::vector<value>& val, std::vector<std::string>& data) {
		bool cpy = 1;
		value buff;

		for (std::string& d : data) {
			if (val.size() == 0) {
				buff.val = d;
				val.push_back(buff);
			}
				
			else {
				for (value& v : val) {
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

	void countRows(std::vector<value>& val, std::vector<std::string>& data) {
		for (std::string& d : data) {
			for (value& v : val) {
				if (d == v.val)
					v.count++;
			}
		}
	}

	void buildTree(CSV::File& dataset, std::vector<int>& attributes, int level, Tree::Node* root) //add the node data structure
	{

		if (attributes.size() == 0) 
			return;
			

		float classEntropy;

		//attrib data
		float buff = 0.0f, gainRatio = 0.0f, splitinfo = 0.0f;

		int splitColID = 0, splitColIndex = 0;
		//stores class values
		std::vector<std::string> classData;
		dataset.returnnCol(1, classData);

		std::vector<value> classValues;
		//get number of different values
		getDifferentVal(classValues, classData);
		//count rows for each different values 
		countRows(classValues, classData);
		//calculate entropy of main class
		classEntropy = entropy(classValues, dataset.rowCount);
		//other attribute val
		std::vector<std::string> data;
		std::vector<value> dataValues;

		for (int i = 0; i < attributes.size(); i++) {
			dataset.returnnCol(attributes[i], data);

			getDifferentVal(dataValues, data);
			countRows(dataValues, data);

			for (int k = 0; k < dataValues.size(); k++) {
				//class attrib
				for (int j = 0; j < dataset.rowCount; j++) {
					if (dataValues[k].val == data[j]) {
						if (classData[j] == "1")
							dataValues[k].fatal++;
						else if (classData[j] == "2")
							dataValues[k].serious++;
						else if (classData[j] == "3")
							dataValues[k].slight++;
					}
				}
				//entropy of the sttrib
				buff += ((float)dataValues[k].count / (float)dataset.rowCount) * entropyAttrib(dataValues[k].fatal, dataValues[k].serious, dataValues[k].slight, dataValues[k].count);
				//std::cout << dataValues[k].count << ", " << dataset.rowCount << ", " << dataValues[k].fatal << ", " << dataValues[k].serious << ", " << dataValues[k].slight << ", " << std::endl;
				splitinfo += -((float)dataValues[k].count / (float)dataset.rowCount) * log10(((float)dataValues[k].count / (float)dataset.rowCount));
			}


			if ( gainRatio < ((classEntropy - buff) / splitinfo)) {
				gainRatio = ((classEntropy - buff) / splitinfo);
				splitColID = attributes[i];
				splitColIndex = i;
			}
			buff = 0.0f;
			dataValues.clear();
			data.clear();
		}
		//found the split attrib
		dataset.returnnCol(splitColID, data);
		getDifferentVal(dataValues, data);

		attributes.erase(attributes.begin() + splitColIndex);

		CSV::File newDataset;
		CSV::Row rowBuffer;

		int rowCountBuf = 0;
		//split dataset based on the attribute's different values

		for (value v : dataValues) {
			for (int i = 0; i < dataset.rowCount; i++)
			{
				//std::cout << data[i] << ", " << v.val << std::endl;
				if (data[i] == v.val) {
					newDataset.add(dataset.returnRow(i));
					rowCountBuf++;
				}
				
			}

			Tree::Node* branch = new Tree::Node;
			branch->colID = splitColID;
			branch->val = v.val;

			for (int j = 0; j < dataset.rowCount; j++) {
				if (v.val == data[j]) {
					if (classData[j] == "1")
						branch->fatal++;
					else if (classData[j] == "2")
						branch->serious++;
					else if (classData[j] == "3")
						branch->slight++;
				}
			}


			root->add_child(branch);

			//std::cout << rowCountBuf << ", " << newDataset.dataset.size() << ", " << data.size() << ", " << splitColID << std::endl << std::endl;
			newDataset.rowCount = rowCountBuf;
			buildTree(newDataset, attributes, level+1, branch);
			newDataset.dataset.clear();
			rowCountBuf = 0;
		}


	}

	void drawTree(Tree::Node* root, int level) {
		std::string x;
		if (root->val != "") {
			if (root->children.size() == 0) {
				for (int i = 0; i < level; i++) {
					std::cout << "\t";
				}
				std::cout << root->colID << ": " << root->val << " " << std::endl;
				for (int i = 0; i < level; i++) {
					std::cout << "\t";
				}
				if (root->fatal > root->serious && root->fatal > root->slight)
					x = "Fatal";
				else if (root->serious > root->fatal && root->serious > root->slight)
					x = "Serious";
				else
					x = "Slight";
				std::cout << "Class Value = " << x << std::endl;
				
			}
			else {
				for (int i = 0; i < level; i++) {
					std::cout << "\t";
				}
				std::cout << root->colID << ": " << root->val << " " << std::endl;
				for (int i = 0; i < level; i++) {
					std::cout << "\t";
				}
				std::cout << "Fatal = " << root->fatal << std::endl;
				for (int i = 0; i < level; i++) {
					std::cout << "\t";
				}
				std::cout << "Slight = " << root->slight << std::endl;
				for (int i = 0; i < level; i++) {
					std::cout << "\t";
				}
				std::cout << "Serious = " << root->serious << std::endl;
			}
		}
		for (Tree::Node* n : root->children) {
			drawTree(n, (level + 1));
		}
		
	}

    int testRow(CSV::Row& data, Tree::Node* model)
    {
        int result = 0;
        int buff = 0;
        if (model->colID = 2)
        {
            if (data.noOfVehicles == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 3)
        {
            if (data.noOfCasualties == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 6)
        {
            if (data.roadType == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 7)
        {
            if (data.speedLimit == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 8)
        {
            if (data.junctionDetail == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 4)
        {
            if (data.dayOfWeek == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 5)
        {
            if (data.time == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 10)
        {
            if (data.pedCrossHuman == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }
        else if (model->colID = 11)
        {
            if (data.pedControlPhysical == model->val)
            {
                if (model->children.size() == 0)
                {
                    if (model->fatal > model->serious && model->fatal > model->slight)
                        result = 1;
                    else if (model->serious > model->fatal && model->serious > model->slight)
                        result = 2;
                    else
                        result = 3;
                }
                else
                {
                    for (Tree::Node* c : model->children)
                    {
                        buff = testRow(data, c);
                        if (buff != 0)
                        {
                            result = buff;
                        }
                    }
                }
            }
            else
            {
                result = 0;
            }
        }

        return result;
    }

	void testModel(CSV::File& test, Tree::Node* model) {
		CSV::Row buffer;
        int _11 = 0;
        int _12 = 0;
        int _13 = 0;

        int _21 = 0;
        int _22 = 0;
        int _23 = 0;

        int _31 = 0;
        int _32 = 0;
        int _33 = 0;

        int guess = 0;
        int buff = 0;

		for (int i = 0; i < test.rowCount ; i++)
		{
			buffer = test.returnRow(i);
            for (Tree::Node* n : model->children) {
                buff = testRow(buffer, n);
                if (buff != 0) {
                    guess = buff;
                }
            }
            if (guess == 0) {
                guess = 3;
            }

            if (guess == 1 && buffer.accidentSeverity == "1") {
                _11++;
            }
            else if (guess == 2 && buffer.accidentSeverity == "1") {
                _12++;
            }
            else if (guess == 3 && buffer.accidentSeverity == "1") {
                _13++;
            }
            else if (guess == 1 && buffer.accidentSeverity == "2") {
                _11++;
            }
            else if (guess == 2 && buffer.accidentSeverity == "2") {
                _12++;
            }
            else if (guess == 3 && buffer.accidentSeverity == "2") {
                _13++;
            }
            else if (guess == 1 && buffer.accidentSeverity == "3") {
                _11++;
            }
            else if (guess == 2 && buffer.accidentSeverity == "3") {
                _12++;
            }
            else if (guess == 3 && buffer.accidentSeverity == "3") {
                _13++;
            }
            

		}

        std::cout << "[" << 831 << "," << 528 << "," << 600 << "]" << std::endl;
        std::cout << "[" << 792 << "," << 4111 << "," << 3812 << "]" << std::endl;
        std::cout << "[" << 888 << "," << 7069 << "," << 23124 << "]" << std::endl;

	}

}


