#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <stdio.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "b.h"
#include "connect.h"
#include "exec.h"

using namespace std;

// void deleteConn(vector<char*> &vect);
// Base* makeTree (vector<vector<char*> > root);
// void goodbye(Base* whatever);
    
// int main() {
//     vector <char*> aand;
//     char *amp = new char('&');
//     aand.push_back(amp);
//     vector <char*> oor;
//     char *line = new char('|');
//     oor.push_back(line);
//     vector <char*> semi;
//     char *scolon = new char(';');
//     semi.push_back(scolon);
//     /*----ADDING PARENTHESES for ASSN3-----*/
//     vector<char*> sPa;
//     char *sP = new char('(');
//     sPa.push_back(sP);
//     vector<char*> ePa;
//     char *eP = new char(')');
//     ePa.push_back(eP);
//     /*--------------------------------------*/
    
    
//     while(1==1) {
//         vector<vector<char*> > commands;
//         string input = "";
//         cout << "$ ";
//         getline(cin, input);
//         string terminate = input.substr(0, 4);
//         if (terminate == "exit") {
//             return 0;
//         }
//         /*checking for comments*/
//         else if (input.find('#') != string::npos) {
//             input = input.substr(0, input.find('#'));
//         }
//         /* copying string to char array*/
//         char ex[input.size()];
//         /*for (int i = 0; i < input.size(); i++) { 
//             ex[i] = input.at(i);
//         }
//         */
//         strcpy(ex, input.c_str());
//         /*
//         for (int k = 0; k < input.size(); k++) {
//             cout << ex[k];
//         }
//         cout << endl;
//         */
//         char* token;
//         token = strtok(ex, " ");
//         char* first = token;
//         char* last = &(token[strlen(token) - 1]);
//         bool connector;
//         while (token != NULL) {
//             if (commands.size() == 0) {
//                 vector<char*> temp;
//                 temp.push_back(token); 
//                 commands.push_back(temp); 
//                 connector = false;

//                 while (*first == '(') {
//                     commands.insert(commands.begin(), sPa);
//                     char* l= commands.back().back();
//                     memmove(l, l+0, strlen(l));
//                     connector = false;
//                     first = commands.back().at(0);
//                     }
                    
//                 if (*last == ';') {
//                     deleteConn(commands.back());
//                     connector = true; 
//                 }
//             }
//             else {
//                 if (connector) {
//                     vector <char*> add; 
//                     add.push_back(token);
//                     commands.push_back(add);
//                     connector = false;
                    
//                     if (*first == '(') {
//                         while (*first == '(' ) {
//                             commands.insert(commands.begin() + (commands.size() + 1 ), sPa);
//                             char* l= commands.back().back();
//                             memmove(l, l+0, strlen(l));
//                             connector = false;
//                             first = commands.back().back();
//                         }
//                     }
                    
                    
//                     if (*last == ';') {
//                         deleteConn(commands.back());
//                         commands.push_back(semi);
//                         connector = true;
//                     }
//                 }
//                 else if (*last == '&') {
//                     commands.push_back(aand);
//                     connector = true;
//                 }
//                 else if (*last == '|' ) {
//                     commands.push_back(oor);
//                     connector = true;
//                 }
//                 else {
                    
//                     if(*last == ';') {
//                         commands.back().push_back(token);
//                         deleteConn(commands.back());
//                         commands.push_back(semi);
//                         connector = true;
//                     }
//                     else if (*last == ')') {
//                         int k = commands.size() - 1;
//                         commands.back().push_back(token);
                
//                         while(*last == ')') {
//                             char* right = commands.back().back();
//                             right[strlen(right) - 1] = 0;
//                             connector = false;
//                             char* temp = commands.at(k).back();
//                             last = &(temp[strlen(temp)-1]);
//                         }
//                         connector = false;
//                     }
//                     else {
//                         commands.back().push_back(token);
//                     }
//                 }
                
//             }
            
//             token = strtok(NULL, " ");
//             if(token != NULL) {
//                 last = &(token[strlen(token)-1]);
//                 first = token;
//             }

//         }
    
//         for (int i = 0; i < commands.size(); ++i)
// 		{
// 			if (*(commands.at(i).front()) == 0)
// 			{
// 				commands.at(i).erase(commands.at(i).begin());
// 			}
// 		}
        
		
//         Base* wow = makeTree(commands);
//         wow->evaluate();
//         goodbye(wow);
        
        
//     }

// return 0;
// }

// void deleteConn(vector<char*> &vect) {
//     char* lastlast = vect.back();
//     lastlast[strlen(lastlast)-1] = 0;
//     return;
// }

// Base* makeTree(vector<vector<char*> > root) {
//     const char* character;
//     queue<vector<char*> > cmd; 
//     stack<vector<char*> > conn; 
//     for (int i = 0; i < root.size(); i++) {
//         character = (const char*) root.at(i).at(0);
//         if ((*character == '|') || (*character == '&') || (*character == ';') ) {
//             if (conn.size() == 0) {
//                 conn.push(root.at(i));
//                 continue;
//             }
//             else if (*(conn.top().at(0)) != '(') {
//             cmd.push(conn.top());
//             conn.pop();
//             }
//             conn.push(root.at(i));
//         }
//         else if (*character != '&' && *character != '|' && *character != ';'&& *character != '(' && *character != ')' ) {
//             cmd.push(root.at(i));
//         }
//         else if (*character == ')' ) {
//             while(*(conn.top().at(0)) != '(' ) {
//                 cmd.push(conn.top());
//                 conn.pop();
//             }
//             conn.pop();
//         }
//         else if (*character == '(' ) {
//             conn.push(root.at(i));
//         }
//     }
    
//     while (conn.size() > 0) {
//         cmd.push(conn.top());
//         conn.pop();
//     }
    
//     Base* ex;
//     stack<Base*> newStack;
//     while (cmd.size() > 0) {
//         character = (const char*)(cmd.front().at(0));
//         if (*character == '|') {
//             ex = new Or(); 
//             Base* right = newStack.top();
//             newStack.pop();
//             Base* left = newStack.top();
//             newStack.pop();
//             ex->MakeRoots(left, right);
//             newStack.push(ex);
//         }
//         else if (*character == '&') {
//             ex = new And();
//             Base* right = newStack.top();
//             newStack.pop();
//             Base* left = newStack.top();
//             newStack.pop();
//             ex->MakeRoots(left, right);
//             newStack.push(ex);
//         }
//         else if (*character == ';') {
//             ex = new Semi();
//             Base* right = newStack.top();
//             newStack.pop();
//             Base* left = newStack.top();
//             newStack.pop();
//             ex->MakeRoots(left, right);
//             newStack.push(ex);
//         }
//         else {
//             ex = new Execute(cmd.front());
//             newStack.push(ex);
//         }
//         cmd.pop();
        
//     }
//     Base* neww= newStack.top();
    
//     while (!newStack.empty()) {
//         newStack.pop();
//     }
//     return neww;
    
// }

// void goodbye(Base* whatever) {
//     if (whatever) {
//         goodbye(whatever->right);
//         goodbye(whatever->left);
//         delete whatever;
//     }
// }

B* makeTree(vector<string> &commands);
void seperate(string cmd, vector<string> &commands);

int main() {
    bool connector = false;
    bool comment = false;
    int start = 0;
    
    while (1 == 1) {
        cout << "$ ";
        string input;
        vector<string> commands;
        getline(cin, input);
        
        if (input.find('#') != string::npos) {
            input = input.substr(0, input.find('#'));
        }
        
        while (input.at(input.size() - 1) == ' ') {
            input.pop_back();
        }
        //seperate(input, commands);
        for (int i = 0; i < input.size(); i++) {
            if (input.at(i) == '#') {
                comment = true;
                break;
            }
            else {
                comment = false;
            }
        }
        for (int i = 0; i < input.size(); i++) {
            if (input.at(i) == ';' || input.at(i) == '|' || input.at(i) == '&'
            ||  input.at(i) == '(' || input.at(i) == ')') {
                connector = true;
                break;
            }
            else {
                connector = false;
            }
        }
        if (connector == false && comment == false) {
            commands.push_back(input);
        }
        else if (connector == false && comment == true) {
            for (int i = 0; i < input.size(); i++) {
                if (input.at(i) == '#') {
                    commands.push_back(input.substr(start, i - start));
                }
            }
        }
        else if (connector) {
            for (int i = 0; i < input.size(); i++) {
                if(input.at(i) == ';') {
                    commands.push_back(input.substr(start, i - start));
                    commands.push_back(";");
                    i++;
                    start = i + 1;
                }
                else if (input.at(i) == '&') {
                    if (input.at(i + 1)) {
                        commands.push_back(input.substr(start, i - 1 - start));
                        commands.push_back("&");
                        i = i + 2;
                        start = i + 1;
                    }
                }
                else if (input.at(i) == '|') {
                    if (input.at(i+1) == '|') {
                        commands.push_back(input.substr(start, i - 1 - start));
                        commands.push_back("|");
                        i = i + 2;
                        start = i + 1;
                    }
                    else {
                        commands.push_back(input.substr(start, i - start));
                        commands.push_back("%");
                        i = i + 1;
                        start = i + 1;
                    }
                }
                else if (input.at(i) == '(') {
                    commands.push_back("(");
                    i = i + 1;
                    start = i + 1;
                }
                else if (input.at(i) == ')') {
				    if (i == (input.size() - 1) && (comment == false)) {
					    commands.push_back(input.substr(start, i - start));
					    commands.push_back(")");
				    } 
			    	else {
					    if (input.at(i + 1) == ' ') {
						    if (input.at(i + 2) == '&' && input.at(i + 3) == '&') {
							    commands.push_back(input.substr(start, i - start));
							    commands.push_back(")");
							    commands.push_back("&");
							    i = i + 4;
							    start = i + 1;
						    }
						
						    else if (input.at(i + 2) == '|' && input.at(i + 3) == '|') {
							    commands.push_back(input.substr(start, i - start));
							    commands.push_back(")");
							    commands.push_back("|");
							    i = i + 4;
							    start = i + 1;
						    }
					    }
					
					else if (input.at(i + 1) == ';') {
						commands.push_back(input.substr(start, i - start));
						commands.push_back(")");
						commands.push_back(";");
						i = i + 2;
						start = i + 1;
					}
					
					else if (input.at(i + 1) == ')') {
						commands.push_back(input.substr(start, i - start));
						commands.push_back(")");
						commands.push_back(")");
						i = i + 2;
						start = i + 1;
					}
				}
            }
            
            else if (i == (input.size() - 1) && comment == false) {
                commands.push_back(input.substr(start, i - start + 1));
            }
        }
        
        
        makeTree(commands)->evaluate(0, 1);
    }
    
}
return 0;
}


B* makeTree(vector<string> &commands) {
    stack<B*> nStack;
    stack<string> stack;
    queue<string> queue;
    
    B* ex;
    
    for (int i = 0; i < commands.size(); i++) {
        if (commands.at(i) == ";" || commands.at(i) == "|" || commands.at(i) == "&" 
        ||  commands.at(i) == "%") {
            if (stack.empty ()) {
                stack.push(commands.at(i));
                continue;
            }
            else if (stack.top() != "(") {
                queue.push(stack.top());
                stack.pop();
            }
            stack.push(commands.at(i));
        }
        else if (commands.at(i) != ";" && commands.at(i) != "|" && commands.at(i) != "&" 
        &&  commands.at(i) != "%") {
            queue.push(commands.at(i));
        }
        else if (commands.at(i) == "(") {
            stack.push(commands.at(i));
        }
        else if (commands.at(i) == ")") {
            while (stack.top() != "(") {
                queue.push(stack.top());
                stack.pop();
            }
            stack.pop();
        }
    }
    
    while (!(stack.empty())) {
        queue.push(stack.top());
        stack.pop();
    }
    
    // stack<Base*> newStack;
    // Base* ex;
    
    while (!(nStack.empty())) {
        nStack.pop();
    }
    
    bool checker = false;
    
    while (!(queue.empty())) {
        if (queue.front() == "&") {
            ex = new And();
            checker = false;
        }
        else if (queue.front() == ";") {
            ex = new Semi();
            checker = false;
        }
        else if (queue.front() == "|") {
            ex = new Or();
            checker = false;
        }
        /*----ASSN4-----------*/
        else if (queue.front() == "%") {
            ex = new Pipe();
            checker = false;
        }
        /*--------------------*/
        else {
            ex = new Execute(queue.front());
            checker = true;
        }
        
        if(checker) {
            nStack.push(ex);
        }
        else {
            B* right = nStack.top();
            nStack.pop();
            B* left = nStack.top();
            nStack.pop();
            ex->MakeRoots(left, right);
            nStack.push(ex);
        }
        queue.pop();
    }
    
    B* neww = nStack.top();
    while (!nStack.empty()) {
        nStack.pop();
    }
    return neww;
}

