#include "DecisionTree.h"
#include <iostream>


namespace DecisionTree {

	float entropy(int* val, int size, int count) {
		float result = 0;
		for (int i = 0; i < size; i++)
		{
			float x = (float)val[i] / (float)count;
			result += (-x) * log10(x);
		}

		return result;
	}
}


