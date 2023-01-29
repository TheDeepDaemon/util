#ifndef DEBUGGING_UTIL_H
#include<iostream>
#include<string>


// purely for giving a message when failed assert
bool failedAssertMessage(const std::string& message) {
	std::cout << message << '\n';
	return false;
}


#endif // !DEBUGGING_UTIL_H