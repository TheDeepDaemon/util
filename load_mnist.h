#ifndef LOAD_MNIST_H
#define LOAD_MNIST_H
#include<vector>
#include<string>
#include"file_util.h"


using std::vector;
using std::pair;


inline vector<pair<int, vector<int>>> loadMnist(const string& MNIST_FILENAME) {

    vector<char> raw = slurp(MNIST_FILENAME);

    size_t i = 0;

    string line = "";

    while (raw[i] != ',' && i < raw.size()) {
        line += raw[i];
        i++;
    }
    i++;

    size_t numLines = stoi(line);
    line.clear();

    while (raw[i] != '\n' && i < raw.size()) {
        line += raw[i];
        i++;
    }
    i++;

    size_t lineSize = stoi(line);
    line.clear();

    vector<pair<int, vector<int>>> data(numLines,
        pair<int, vector<int>>(0, vector<int>(lineSize)));

    size_t dataIterator = 0;

    while (i < raw.size() && dataIterator < data.size()) {

        data[dataIterator].first = (int)raw[i++];

        for (size_t j = 0; j < lineSize && i < raw.size(); j++, i++) {
            data[dataIterator].second[j] = (unsigned char)raw[i];
        }

        dataIterator++;
    }

    return data;
}


vector<pair<int, vector<int>>> loadMnistTrain() {
    return loadMnist("C:\\Users\\ehp17\\OneDrive\\Libraries\\Util\\Util\\mnist_train.dat");
}

vector<pair<int, vector<int>>> loadMnistTest() {
    return loadMnist("C:\\Users\\ehp17\\OneDrive\\Libraries\\Util\\Util\\mnist_test.dat");
}




#endif // !LOAD_MNIST_H