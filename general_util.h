#ifndef GENERAL_UTIL_H
#define GENERAL_UTIL_H
#include<time.h>
#include<iostream>
#include<string>
#include<vector>


inline void consolePause() {
	std::cout << "\n\nPress enter to continue...";
	std::cin.get();
	std::cout << std::endl;
}


template<typename T>
inline void print(const T& val, const std::string& end = "\n") {
	std::cout << val << end;
}


template<typename T, typename U>
inline void print(const T& val1, const U& val2, const std::string& sep = " ", const std::string& end = "\n") {
	std::cout << val1 << sep << val2 << end;
}


template<typename T>
inline void print(const std::vector<T>& vec, const std::string& sep = ", ", const std::string& end = "\n") {
	for (uint i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << sep;
	}
	std::cout << end;
}


#endif