#ifndef BASE_H
#define BASE_H

#include <string>
using namespace std;

class Base{
public:
    Base *left;
    Base *right;
	Base() {} 
	void set(Base *left, Base *right) {
	    this->left = left;
	    this->right = right;
	}
	virtual bool evaluate(int in, int out) = 0;
};
#endif