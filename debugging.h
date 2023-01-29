#ifndef DEBUGGING_UTIL_H
#include<iostream>
#include<string>

using std::cout;
using std::string;

// purely for giving a message when failed assert
bool failedAssertMessage(const string& message) {
	cout << message << '\n';
	return false;
}


#endif // !DEBUGGING_UTIL_H