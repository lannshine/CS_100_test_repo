#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "base.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class Connector: public Base
{
	public:
		Connector() : Base() {}
		virtual bool evaluate(int in, int out) = 0; 
};

class Semi:public Connector
{
	public:
		Semi();
		bool evaluate(int in, int out);
};

class Or : public Connector
{
	public:
		Or();
		bool evaluate(int in, int out);
};

class And : public Connector
{
	public:
		And();
		bool evaluate(int in, int out);
};

class Pipe : public Connector
{
	public:
	Pipe();
	bool evaluate(int in, int out);
};

#endif