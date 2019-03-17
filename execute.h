#ifndef EXECUTE_H
#define EXECUTE_H
#include <vector>
#include <iostream>
#include "base.h"

using namespace std;

class Execute: public Base {
	protected:
		vector<string> command;
		string in;
		string out;

	public:
		Execute() : Base() {}
		Execute(string str);
		Execute(vector<string> ex);
		bool evaluate(int start, int end);
};

#endif