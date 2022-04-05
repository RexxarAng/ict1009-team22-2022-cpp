#ifndef ICT1009_TEAM22_2022_CPP_REPOSITORY_H
#define ICT1009_TEAM22_2022_CPP_REPOSITORY_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "screen_utility.h"

using namespace std;

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
        cout << "No records loaded" << endl;
        ScreenUtility::pause();
    }
    else {
        cout << "Loading records..." << endl;
        while (!dataSourceFile.eof()) {
            columns.clear();
            getline(dataSourceFile, line);

            if (line.empty()) continue;

            stringstream s(line);
            while (getline(s, word, ',')) {
                columns.push_back(word);
            }

            try {
                T* dataModel = new T();
                dataModel->deserialize(line);
                this->records.insert(this->records.begin(), dataModel);
            }
            catch (exception& e) {
                cout << "Record not loaded due to : " << e.what() << endl;
            }

            if (dataSourceFile.eof())
                break;
        }

        cout << "Printing out all records" << endl;
        for (T* i : this->records) {
            cout << i->serialize() << endl;
        }
        dataSourceFile.close();
    }
    return true;
}

template <typename T>
bool Repository<T>::save() {
    fstream dataSourceFileOut;

    try {
        dataSourceFileOut.open(this->filename, ios::trunc | ios::out);
        for (T* i : this->records) {
            //cout << i->getTitle() << "\n";
            dataSourceFileOut << i->serialize() << "\n";
        }
        dataSourceFileOut.close();
        //cout << "saved to " << this->filename << endl;
        //ScreenUtility::pause();
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
