// ExplorationScratchPad.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

using namespace std;

int main()
{
	vector<int> vec; //actual instance
	vector<int> * pvec = &vec; //pointer to that instance, mutable
	vec.push_back(1);
	vector<int> cvec = vec; //copy constructor
	pvec->push_back(2);
	printf("Something wicked this way comes");
    return 0;
}

