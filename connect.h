#ifndef CONNECT_H
#define CONNECT_H
#include "b.h"
#include <cstdlib>
#include <string>
#include <iostream>

class Connector : public B {
    public:
    Connector() : B() {}
    virtual bool evaluate(int in, int out) = 0;
};

class Or : public Connector {
    public:
    Or();
    bool evaluate(int in, int out); 
};

class And : public Connector {
    public:
    And(){};
    bool evaluate(int in, int out);
};

class Semi : public Connector {
    public:
    Semi(){};
    bool evaluate(int in, int out);
};

class Pipe : public Connector {
    public:
    Pipe(){};
    bool evaluate(int in, int out);
};

#endif