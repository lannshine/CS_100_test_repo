#include "connect.h"
#include "b.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>	
#include <string.h>

/*---Or------------------*/
Or::Or() : Connector() {}
bool Or::evaluate(int in, int out) {
    if ((left->evaluate(0, 1) == true) || (right->evaluate(0, 1) == true)) {
        return true;
    }
    else {
        return false;
    }
}

/*---And-------------------*/
//And::And() {}
bool And::evaluate(int in, int out) {
    if ((left->evaluate(0, 1) == true) && (right->evaluate(0, 1) == true)){
        return true;
    }
    else {
        return false;
    }
}

/*---Semi----------------------*/
//Semi::Semi() {}
bool Semi::evaluate(int in, int out) {
    left->evaluate(0, 1);
    if(right->evaluate(0, 1)) {
        return true;
    }
    else {
        return false;
    }
}

bool Pipe::evaluate(int in, int out) {
    int piper[2];
    pipe(piper);
    
    left->evaluate(in, piper[1]);
    close(piper[0]);
    return true;
}


