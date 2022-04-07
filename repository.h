#ifndef ICT1009_TEAM22_2022_CPP_REPOSITORY_H
#define ICT1009_TEAM22_2022_CPP_REPOSITORY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "screen_utility.h"

using namespace std;

//Funtion prototyping from helper.h
vector<string> readCSVRow(const string &row, char separator);

template <typename T>
class Repository {
private:
    string filename;
    vector<T*> records;
public:
    explicit Repository(const string& filename);
    bool load();
    bool save();
    vector<T*>* getRecords();
};

template <typename T>
Repository<T>::Repository(const string& filename) {
    this->filename = filename;
}
template <typename T>
bool Repository<T>::load() {
    this->records.clear();

    ifstream dataSourceFile;
    vector<string> columns;
    string word, line;

    dataSourceFile.open(this->filename);
    if (!dataSourceFile) {
        throw ParseFileNotFoundException(typeid(this).name(), filename);
    }
    cout << "Loading records..." << endl;
    while (!dataSourceFile.eof()) {
        columns.clear();
        getline(dataSourceFile, line);
            
        if (line.empty()) continue;
        auto fields = readCSVRow(line); //returns a vector of strings
        for(string i: fields){
            columns.push_back(i);
        }
            
        /*stringstream s(line);
        while (getline(s, word, ',')) {
            columns.push_back(word);
        }*/

        try {
            T* dataModel = new T();
            dataModel->deserialize(line);
            this->records.insert(this->records.end(), dataModel);
        }
        catch (ParseException& e) {
            cout << e.what() << endl;
            ScreenUtility::pause();
        }
        if (dataSourceFile.eof())
            break;
    }
    cout << "Printing out all records" << endl;
    for (T* i : this->records) {
        cout << i->serialize() << endl;
    }
    dataSourceFile.close();
    
    return true;
}

template <typename T>
bool Repository<T>::save() {
    fstream dataSourceFileOut;

    try {
        dataSourceFileOut.open(this->filename, ios::trunc | ios::out);
        for (T* i : this->records) {
            dataSourceFileOut << i->serialize() << "\n";
        }
        dataSourceFileOut.close();
        return true;
    }
    catch(exception& e) {
        dataSourceFileOut.close();
        return false;
    }
}

template <typename T>
vector<T*>* Repository<T>::getRecords() {
    return &records;
}


#endif //ICT1009_TEAM22_2022_CPP_REPOSITORY_H
