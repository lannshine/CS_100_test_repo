#include "exec.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>	
#include <string.h>
#include <string>
#include <fcntl.h>
#include <algorithm>
#include <iterator>
using namespace std;

Execute::Execute(vector<string> cd) {
    for (int i = 0; i < cd.size(); i++) {
        command.push_back(cd.at(i));
    }
}

Execute::Execute(string str) {
    char* ex = new char[str.size() + 1];
    strcpy(ex, str.c_str());
    char* token = strtok(ex, " ");
    
    while (token != NULL) {
        command.push_back(token);
        token = strtok(NULL, " ");
    }
}

bool Execute::evaluate(int in, int out){
    //struct stat buf; /*using stat() call*/
    //int stats = stat(command.back(), &buf);
    int statusCheck;
    /*------------ASSN-3--------------*/
    
    // if (command.at(0) ==  "test" || command.at(0) == "["))) { /*checks for test*/
    //     /*--BRACKETS--*/
    //     if(command.at(0) == "["))) {
    //         command.pop_back();
    //         command.erase(command.begin());
    //     }
    //     else if (command.at(0), "test"))) {
    //         command.erase(command.begin());
    //     }
        
    //     /* running tests */
        
    //     if (stats == -1) {
    //         cout << "(False)" << endl;
    //         return false;
    //     }
        
    //     /*---------Implement -e-------------*/
    //     if (!(strcmp(command.at(0), "-f"))) {
            
    //         if (S_ISREG(buf.st_mode)) {
    //             cout << "(True)" << endl;
    //             return true;
    //         }
    //         else {
    //             cout << "(False)" << endl;
    //             return false;
    //         }
    //     }
        
    //     if (!(strcmp(command.at(0), "-d"))) {
            
    //         if (S_ISREG(buf.st_mode)) {
    //             cout << "(True)" << endl;
    //             return true;
    //         }
    //         else {
    //             cout << "(False)" << endl;
    //             return false;
    //         }
    //     }
    //     else {
        
    //         cout << "(True)" << endl;
    //         return true;
    //     }
        
    // }
    
    
/*--------------END OF ASSN3------------------------*/

    if (command.size() == 0) {
        return false;
    }
    else if (command.at(0) == "exit") {
        _exit(0);
    }
    else {
    
        // command.push_back(NULL);
        // char **pointer = &command[0];
        
        pid_t pid = fork();
        pid_t ex1;
    
        if (pid < 0) {
            cout << "error" << endl;
            exit(1);
        }
        else if (pid == 0) {
            vector<string> ex;
            for (int i = 0; i < command.size(); i++) {
                if ((command.at(i) != "<") && (command.at(i) != ">") && (command.at(i) != ">>")) {
                    ex.push_back(command.at(i));
                }
                else {
                    break;
                }
            }
        
            for (int i = 0; i < command.size() - 1; i++) {
                if (command.at(i) == "<") {
                    ip = command.at(i + 1);
                }
            else if (command.at(i) == ">") {
                op = command.at(i+1);
            }
            else if (command.at(i) == ">>") {
                op = command.at(i+1);
            }
        }
        int arr = ex.size() + 1;
        char* arg[arr];
        for (int i = 0; i <= arr; i++) {
            arg[i] = const_cast<char*>(ex.at(i).c_str()); /* we should use this from now on */
            /*wtf does that do???*/
        }
        arg[arr-1] = NULL;
        int fIn;
        int fOut;
        int f;
        if ((ip.size() > 0) || (op.size() > 0)) {
            if ((ip.size() > 0) && (op.size() > 0)) {
                if (find(command.begin(), command.end(), ">") != command.end()) {
                    fIn = open(ip.c_str(), O_RDWR);
                    fOut = open(op.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
                    
                    if (fIn == -1 || fOut == -1) {
                        perror("Unable to open file");
                        return false;
                    }
                    
                    dup2(fIn, 0);
                    dup2(fOut, 1);
                    close(fIn);
                    close(fOut);
                }
                
                else {
                    fIn = open(ip.c_str(), O_RDWR);
                    fOut = open(op.c_str(), O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRWXG);
                    if(fIn == -1 || fOut == -1) {
                        perror ("Unable to open file");
                        return false;
                    }
                }
                
            }
            else if (ip.size() > 0) {
                f = open(ip.c_str(), O_RDWR);
                if(f == -1) {
                    perror("Unable to open file");
                    return false;
                }
                dup2(f, 0);
                close(f);
            }
            else if (!op.empty()) {
                if(find(command.begin(), command.end(), ">") != command.end()) {
                    f = open(op.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
                    if (f < 0) {
                        perror("Unable to open file");
                        return false;
                    }
                    dup2(f, 1);
                    close(f);
                }
                else {
                    f = open(op.c_str(), O_CREAT | O_APPEND | O_WRONLY, S_IRWXU | S_IRWXG);
                    if(f< 0) {
                        perror("Unable to open file");
                        return false;
                    }
                    dup2(f, 1);
                    close(f);
                }
            }
            dup2(in, 0);
            dup2(out, 1);
            
            if(out != 1) {
                close(out);
            }
            else if (in != 0) {
                close(in);
            }
            if (execvp(*arg, arg) < 0) {
                cout << "ERROR: exec failed" << endl;
                exit(1);
            }
        }
        else {
            char* argg[command.size() + 1];
            for (int i = 0; i < command.size(); i++) {
                argg[i] = const_cast<char*>(command.at(i).c_str());
            }
            argg[command.size()] = NULL;
            dup2(in, 0);
            dup2(out, 1);
            if (out != 0) {
                close(out);
            }
            else if (in != 0) {
                close(in);
            }
            if (execvp(*argg, argg) < 0) {
                cout <<"Error: exec failed" << endl;
                exit(1);
            }
        }
        
    }
    else {
        ex1 = waitpid(pid, &statusCheck, 0);
        if (ex1 == -1) {
            exit(EXIT_FAILURE);
        }
        if (WEXITSTATUS(statusCheck) == 0) {
            return true;
        }
    }
    }
    
    return false;
    /*
    else if (pid == 0) {
        if (execvp(pointer[0], pointer) == -1) {
            perror ("exec");
            return false;
        }
    }
    
    if (pid > 0) {
        if (waitpid(0, NULL, 0) == -1) {
            perror ("wait");
        }
    }
    */
    
}