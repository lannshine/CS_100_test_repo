#include <stack>
#include <queue>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "connector.h"
#include "base.h"
#include "execute.h"

using namespace std;


Base* makeTree(vector<string> &cmds) {
	stack< Base* > theStack;
	stack<string> stack; 
	queue<string> q;
	bool checker = false;
	
	for (int i = 0; i < cmds.size(); i++) {
			if (cmds.at(i) == ";" || cmds.at(i) == "|" || cmds.at(i) == "&" || cmds.at(i) == "%") 
			{ 
				if (stack.empty()) {
					stack.push(cmds.at(i));
					continue;
				}
				else if (stack.top() != "(") {
					q.push(stack.top());
					stack.pop();
				}
				
				stack.push(cmds.at(i));
			}
			else if (cmds.at(i) != ";" && cmds.at(i) != "|" && cmds.at(i) != "&" && cmds.at(i) != "(" && cmds.at(i) != ")" && cmds.at(i) != "%") {
				q.push(cmds.at(i));
			}
			
			else if (cmds.at(i) == "(") {
				stack.push(cmds.at(i));
			}
			else if (cmds.at(i) == ")") {
			
				while (stack.top() != "(") {
					q.push(stack.top());
					stack.pop();
				}
				
				stack.pop();
			}
			
	}
	
	while (!stack.empty()) {
				q.push(stack.top());
				stack.pop();
	}
	
	
	while (!theStack.empty()) {
			theStack.pop(); 
	}
	
	Base* ex;
	
	while (!q.empty()) {

		if (q.front() == "&") { 
			ex = new And();
			checker = false;
		}
		else if (q.front() == "%") {
			ex = new Pipe();
			checker = false;
		}
		else if (q.front() == ";") { 
			ex = new Semi();
			checker = false;
		}
		else if (q.front() == "|") { 
			ex = new Or();
			checker = false;
		}
		else {
			ex = new Execute(q.front());
			checker = true;
		}

		if (checker) {
				theStack.push(ex);
		}
		else {
			Base* rhs = theStack.top();
			theStack.pop();
			Base* lhs = theStack.top();
			theStack.pop();
			ex->set(lhs, rhs);
			theStack.push(ex);
		}
			
		q.pop();
	}

	Base* start = theStack.top();
	while (!theStack.empty()) {
			theStack.pop();
	}

	return start;
}

int main() {
	bool connector = false;
	bool comment = false; 
	int start = 0;
	while(1) {
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
			if (input.at(i) == ';' || input.at(i) == '&' || input.at(i) == '|' || input.at(i) == '(' || input.at(i) == ')') {
				connector = true; 
				break; 
			}
		
			connector = false; 
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
	
		else if (connector == true) {
			for (int i = 0; i < input.size(); i++) {
				if (input.at(i) == ';') {
					commands.push_back(input.substr(start, i - start));
					commands.push_back(";");
					i = i + 1;
					start = i + 1;
				}
				else if (input.at(i) == '&') {
					if (input.at(i + 1) == '&') {
						commands.push_back(input.substr(start, i - 1 - start));
						commands.push_back("&");
						i = i + 2;
						start = i + 1;
					}
				}
			
				else if (input.at(i) == '|') {
					if (input.at(i + 1) == '|') {
						commands.push_back(input.substr(start, i - 1 - start));
						commands.push_back("|");
						i = i + 2;
						start = i + 1;
					}
				
					else {
						commands.push_back(input.substr(start, i - start));
						commands.push_back("%"); /*differentiating between pipe and Or */
						i = i + 1;
						start = i + 1;
					}
				}
			
				else if (input.at(i) == '(') {
					commands.push_back("(");
					start = i + 1;
				}
			
				else if (input.at(i) == ')') {
					if (i == (input.size() - 1) && comment == false) {
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
		}
		
		makeTree(commands)->evaluate(0, 1); 
	}	
	
	return 0;
}