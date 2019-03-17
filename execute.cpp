#include "execute.h"
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

Execute::Execute(string str) {
	char * cstr = new char[str.size() + 1];
	strcpy(cstr, str.c_str());
	char * token = strtok(cstr, " ");

	while (token != NULL) {
		command.push_back(token);
		token = strtok(NULL, " ");
	}
}

Execute::Execute(vector<string> ex) {
	for (int i = 0; i < ex.size(); ++i) {
		command.push_back(ex.at(i));
	}
}

bool Execute::evaluate(int start, int end) {
	vector<string> temp;
	if (command.at(0) == "test" || command.at(0) == "[") {
		if (command.at(0) == "[") {
			if (command.at(command.size() - 1) != "]") {
				cout << "Uneven brackets, please fix." << endl;
				return false;
			}
		}

		struct stat buf;
		
		if (command.at(1) == "-d") {
			if (stat(const_cast<char*>(command.at(2).c_str()), &buf) != 0) {
				cout << "unable to access " << command.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
					
			else if (buf.st_mode & S_IFDIR) {
				cout << "(True)" << endl;
				return true;
			}
					
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		else if (command.at(1) == "-e") {
			if (stat(const_cast<char*>(command.at(2).c_str()), &buf) != 0) {
				cout << "unable to access " << command.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
			else {
				cout << "(True)" << endl;
				return true;
			}
		}
		
		else if (command.at(1) == "-f") {
			if (stat(const_cast<char*>(command.at(2).c_str()), &buf) != 0) {
				cout << "unable to access " << command.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
					
			else if (buf.st_mode & S_IFREG) {
				cout << "(True)" << endl;
				return true;
			}
					
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		
		else {
			if (stat(const_cast<char*>(command.at(1).c_str()), &buf) != 0) {
				cout << "unable to access " << command.at(1) << endl;
				cout << "(False)" << endl;
				return false;
			}
					
			else {
				cout << "(True)" << endl;
				return true;
			}
		}
	}
	if (command.at(0) == "exit") {
		exit(0);
	}
	else { /*no test*/
		pid_t pid = fork();
		pid_t dub;
		int statusCheck;
		if (pid < 0) { 
			cout << "ERROR: forking child process failed" << endl;
			exit(1);
		}
		else if (pid == 0) {
			vector<string> temp;
			for (int i = 0; i < command.size(); i++) {
				if (command.at(i) != "<" && command.at(i) != ">" && command.at(i) != ">>") {
					temp.push_back(command.at(i));
				}

				else {
					break;
				}	
			}

			for (int i = 0; i < command.size() - 1; i++) {
				if (command.at(i) == "<") {
					in = command.at(i + 1);
				}

				else if (command.at(i) == ">") {
					out = command.at(i + 1);
				}

				else if (command.at(i) == ">>") {
					out = command.at(i + 1);
				}
			}
			int arrSize = temp.size() + 1;
			char * argument[arrSize];
			for (int i = 0; i < arrSize - 1; ++i) {
				argument[i] = const_cast<char*>(temp.at(i).c_str());
			}
			argument[arrSize - 1] = NULL; 
			if (!in.empty() || !out.empty()) {
				if (!in.empty() && !out.empty()) { 
					if (find(command.begin(), command.end(), ">") != command.end()) {
						int fI = open(in.c_str(), O_RDWR);
						int fO = open(out.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
						
						if (fI == -1 || fO == -1)
						{
							perror("Error: unable to open file");
							return false;
						}
						
						dup2(fI, 0);
						dup2(fO, 1);
						close(fI);
						close(fO);

					}

					else { 
						int fI = open(in.c_str(), O_RDWR);
						int fO = open(out.c_str(), O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRWXG);
						
						if(fI == -1 || fO == -1)
						{
							perror("Error: unable to open file");
							return false;
						}
						
						dup2(fI, 0);
						dup2(fO, 1);
						close(fI);
						close(fO);
					}
				}

				else if (!in.empty()) { 
					int fd = open(in.c_str(), O_RDWR);
					
					if(fd == -1)
					{
						perror("Error: unable to open file");
						return false;
					}
					
					dup2(fd, 0);
					close(fd);
				}

				else if (!out.empty()) { 
					if (find(command.begin(), command.end(), ">") != command.end()) {
						int fd;
						
						fd = open(out.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
						if (fd < 0)
						{
							perror("Error: open failed.");
							return false;
						}
						
						dup2(fd, 1);
						close(fd);
					}
					else { 
						int fd;
						
						fd = open(out.c_str(), O_CREAT | O_APPEND | O_WRONLY, S_IRWXU | S_IRWXG);
						if(fd < 0)
						{
							perror("Error: open failed.");
							return false;
						}
						dup2(fd, 1);
						close(fd);
					}
				}
				dup2(start, 0);
				dup2(end, 1);

				if (start != 0) {
					close(start);
				}
				else if (end != 1) {
					close(end);
				}

				if (execvp(*argument, argument) < 0) {
					cout << "ERROR: exec failed" << endl;
					exit(1);
				}
			}
			else {
				char* arg[command.size() + 1];
				for (int i = 0; i < command.size(); ++i) {
					arg[i] = const_cast<char*>(command.at(i).c_str());
				}
				arg[command.size()] = NULL;
				dup2(start, 0);
				dup2(end, 1);
				if (start != 0) {
					close(start);
				}
				else if (end != 1) {
					close(end);
				}

				if (execvp(*arg, arg) < 0) { 
					cout << "ERROR: exec failed" << endl;
		            exit(1);
				}
			}
		}
		else {
			dub = waitpid(pid, &statusCheck, 0);
			if (dub == -1) {
				exit(EXIT_FAILURE);
			}
				
			if (WEXITSTATUS(statusCheck) == 0) {
				return true;
			}
		}
	}
	return false;
}
