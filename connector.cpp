#include "connector.h"
#include "base.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>	
#include <string.h>


using namespace std;

Semi::Semi() : Connector() {}

bool Semi::evaluate(int start, int end) {
	left->evaluate(0, 1);
    if(right->evaluate(0, 1)) {
        return true;
    }
    else {
        return false;
    }
}

Or::Or() : Connector() {}

bool Or::evaluate(int start, int end) {
	if ((left->evaluate(0, 1) == true) || (right->evaluate(0, 1) == true)) {
        return true;
    }
    else {
        return false;
    }
}


And::And() : Connector() {}

bool And::evaluate(int start, int end) {
	if ((left->evaluate(0, 1) == true) && (right->evaluate(0, 1) == true)){
        return true;
    }
    else {
        return false;
    }
}

Pipe::Pipe() : Connector() {}

bool Pipe::evaluate(int in, int out) {
	int fileD[2];
	pipe(fileD);
	left->evaluate(in, fileD[1]);
	close(fileD[1]);
	right->evaluate(fileD[0], out);
	close(fileD[0]);
	return true;
}