#ifndef LR2_HELP_H
#define LR2_HELP_H

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include "queue.h"
#include "array.h"
#include "hash.h"
#include "stack.h"
#include "slist.h"
#include "set.h"
#include "tree.h"
using namespace std;
const string FILENAME = "C:\\Users\\USTremble\\Desktop\\lr2\\cmake-build-debug\\set.txt";

Array<string> split(string str, char delimiter) {
    Array<string> arr;
    int prevDel = -1;

    for (int i = 0; i < str.size(); i++) {
        if(str[i] == delimiter) {
            arr.pushBack(str.substr(prevDel + 1, i - 1 - prevDel));
            prevDel = i;
        }
    }
    arr.pushBack(str.substr(prevDel + 1, str.size() - prevDel));

    return arr;
}

Set<string> readSet(string name) {
    Set<string> set;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;

    while (getline(file, line)) {
        Array<string> splittedLine = split(line, ' ');

        if (splittedLine.size() != 2) {
            continue;
        }

        if (splittedLine.get(0) == name) {
            Array<string> array = split(splittedLine.get(1), ',');

            for (int i = 0; i < array.size(); i++) {
                set.add(array.get(i));
            }
            return set;
        }
    }

    file.close();

    return set;
}


void writeToFile(string writeline) {
    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }
    Array<string> fileLines;
    string line;

    while (getline(file, line)) {
        fileLines.pushBack(writeline);  //сохраняем строку
    }

    file.close();

    ofstream outFile(FILENAME); //перезаписываем содержимое файла
    if (!outFile.is_open()) {
        throw runtime_error("Error opening file for writing");
    }

    for (int i = 0; i < fileLines.size(); i++) {
        outFile << fileLines.get(i) << endl;
    }

    outFile.close();
}

void checkArgumentCount(Array<string>& parameters, int expected) {
    if (parameters.size() != expected) {
        throw runtime_error("Incorrect count of arguments");
    }
}

void validateElement(const string& element) {
    if (element.find(",") != string::npos) {
        throw runtime_error("',' shouldn't be in the element");
    }
}

void saveSet(const string& name, Set<string>& set) {
    writeToFile(name + " " + set.data.join(','));
}

int toInt(const string& str) {
    int result = 0;
    for (int i = 0; i < str.size(); ++i) {
        char ch = str[i];
        if (ch < '0' || ch > '9') {
            throw invalid_argument("Invalid character in string");
        }
        result = result * 10 + (ch - '0');
    }
    return result;
}


#endif //LR2_HELP_H
