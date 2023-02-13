#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<direct.h>

using std::vector;
using std::ofstream;
using std::ifstream;
using std::string;


// don't use this function on anything with pointer member variables
template<typename T>
inline vector<char> objToRawBytes(const T& obj) {
	vector<char> bytes(sizeof(T));
	memcpy(bytes.data(), &obj, sizeof(T));
	return bytes;
}


template<typename T>
inline vector<char> vecToRawBytes(const vector<T>& vec) {
	size_t numBytes = vec.size() * sizeof(T);
	vector<char> bytes(numBytes);
	memcpy(bytes.data(), vec.data(), numBytes);
	return bytes;
}


// convert between a data type and a buffer of bytes
template<typename T>
union ObjectBuffer {
	T objData;
	char bytes[sizeof(T)];
	ObjectBuffer(const T& obj) {
		objData = obj;
	}

	ObjectBuffer(char* bytes_) {
		memcpy(bytes, bytes_, sizeof(T));
	}

	ObjectBuffer() {
		memset(bytes, 0, sizeof(T));
	}

	void operator=(const T& obj) {
		objData = obj;
	}

};


template<typename T>
inline void copyData(char* dst, const char* src) {
	memcpy(dst, src, sizeof(T));
}


template<typename T>
inline void writeBytesToFile(ofstream& fout, ObjectBuffer<T> obj) {
	fout.write(obj.bytes, sizeof(T));
}


template<typename T>
inline T readBytesFromFile(ifstream& fin) {
	ObjectBuffer<T> obj;
	fin.read(obj.bytes, sizeof(T));
	return obj.objData;
}


// this function writes the contents of a vector to a file
// the vector should be of primitive types or structs with no pointer members
template<typename T>
inline bool writeVectorDataToFile(ofstream& fout, const vector<T>& vec) {
	if (fout.is_open()) {
		fout.write((char*)vec.data(), vec.size() * sizeof(T));
		return true;
	}
	return false;
}


template<typename T>
inline vector<T> readVectorDataFromFile(ifstream& fin, size_t size) {
	if (fin.is_open()) {
		vector<T> vec(size);
		fin.read((char*)vec.data(), size * sizeof(T));
		return vec;
	}
	else {
		return vector<T>();
	}
}


template<typename T>
inline bool writeVectorDataToFile(const string& fileName, const vector<T>& vec) {
	ofstream fout;
	fout.open(fileName);
	bool success = writeVectorDataToFile<T>(fout, vec);
	if (fout.is_open()) {
		fout.close();
	}
	return success;
}


template<typename T>
inline vector<T> readVectorDataFromFile(const string& fileName, size_t size) {
	ifstream fin;
	fin.open(fileName);
	vector<T> vec = readVectorDataFromFile<T>(fin, size);
	if (fin.is_open()) {
		fin.close();
	}
	return vec;
}


template<typename T>
inline bool writeVectorSeriesToFile(ofstream& fout, const vector<vector<T>>& vecs) {
	for (size_t i = 0; i < vecs.size(); i++) {
		if (!writeVectorDataToFile<T>(fout, vecs[i])) {
			return false;
		}
	}
	return true;
}


template<typename T>
inline vector<vector<T>> readVectorSeriesFromFile(ifstream& fin, size_t numVecs, size_t size) {
	vector<vector<T>> vecs;
	vecs.reserve(numVecs);
	for (size_t i = 0; i < numVecs; i++) {
		if (fin.is_open()) {
			vecs.push_back(readVectorDataFromFile<T>(fin, size));
		}
		else {
			return vecs;
		}
	}
	return vecs;
}


/***
* these functions are for converting between vectors of ints and chars;
* this is for the sake of memory.
* Tt is assumed that the ints represent something like an enum,
* and the possible values they can have is within the range of a char.
*/
inline vector<char> convert(const vector<int>& intVec) {
	vector<char> charVec(intVec.size());
	for (size_t i = 0; i < intVec.size(); i++) {
		charVec[i] = intVec[i];
	}
	return charVec;
}


inline vector<int> convert(const vector<char>& charVec) {
	vector<int> intVec(charVec.size());
	for (size_t i = 0; i < charVec.size(); i++) {
		intVec[i] = charVec[i];
	}
	return intVec;
}


// read file, output string that contains all file contents
inline vector<char> slurp(const string& fname) {
	ifstream fin(fname, std::ios::binary | std::ios::ate);

	if (fin.is_open()) {
		std::streamsize fsize = fin.tellg();
		fin.seekg(0, std::ios::beg);

		vector<char> buffer(fsize);
		fin.read(buffer.data(), fsize);
		fin.close();

		return buffer;
	}

	return vector<char>();
}


inline string slurps(const string& fname) {
	vector<char> buffer = slurp(fname);
	return string(buffer.begin(), buffer.end());
}


// generic version of slurp
template<typename T>
inline vector<T> slurp(const string& fname) {
	ifstream fin(fname, std::ios::binary | std::ios::ate);

	if (fin.is_open()) {
		std::streamsize fsize = fin.tellg();
		fin.seekg(0, std::ios::beg);

		vector<T> buffer(fsize / sizeof(T));
		void* bufferPtr = buffer.data();
		fin.read((char*)bufferPtr, fsize);
		fin.close();

		return buffer;
	}

	return vector<T>();
}


template<typename T>
inline void dump(const string& fname, const vector<T>& buffer) {
	ofstream fout;
	fout.open(fname, std::ios::binary);
	const char* ptr = reinterpret_cast<const char*>(buffer.data());
	fout.write(ptr, buffer.size() * sizeof(T));
	fout.close();
}


template<typename T>
inline void dump(const string& fname, const T* buffer, uint64_t size) {
	ofstream fout;
	fout.open(fname, std::ios::binary);
	const char* ptr = reinterpret_cast<const char*>(buffer);
	fout.write(ptr, size * sizeof(T));
	fout.close();
}


inline void dump(const string& fname, const string& buffer) {
	ofstream fout;
	fout.open(fname, std::ios::binary);
	fout.write(buffer.data(), buffer.size());
	fout.close();
}


inline string getBaseFilename(const string& fpath) {
	return fpath.substr(fpath.find_last_of("/\\") + 1);
}


vector<vector<string>> readCsv(const string& fname) {
	vector<vector<string>> csvData;

	std::ifstream fin;
	fin.open(fname);

	if (fin.is_open()) {
		string line;
		string column = "";
		bool isInQuotes = false;

		while (getline(fin, line)) {

			vector<string> thisLine;

			for (size_t i = 0; i < line.size(); i++) {
				char c = line[i];

				if (c == '\"') {
					isInQuotes = !isInQuotes;
				}

				if (c != ',' || isInQuotes) {
					column += c;
				}
				else {
					thisLine.push_back(column);
					column = "";
				}
			}

			thisLine.push_back(column);
			column = "";

			csvData.push_back(thisLine);
		}
	}
	else {
		std::cout << "File failed to open.\n";
	}

	return csvData;
}

#endif // !FILE_UTIL_H