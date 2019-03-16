#ifndef EXEC_H
#define EXEC_H

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include <vector>
#include <stack>
#include <queue>
#include <string>

#include "b.h"

using namespace std;

class Execute : public B {
    private:
        /*vector<char*> command;*/
        vector<string> command;
        string op;
        string ip;
        
    public:
        Execute() : B(){}
        Execute(string str);
        Execute(vector<string> cd); //was a char* before
        bool evaluate(int in, int out);
};
#endif