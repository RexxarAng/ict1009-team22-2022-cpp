#ifndef ICT1009_TEAM22_2022_CPP_REPOSITORY_TEMPLATE_H
#define ICT1009_TEAM22_2022_CPP_REPOSITORY_TEMPLATE_H

#include <string>
#include <sstream>
#include <vector>
#include "repository_exception.h"

using namespace std;

class AbstractDataModel {
protected:
    static vector<string> extractAttributesFromDataString(const string& dataString, char separator = ',') {
        string word;
        vector<string> attributes;
        stringstream ss(dataString);
        while (getline(ss, word, separator)) {
            attributes.push_back(word);
        }
        return attributes;
    }

public:
    virtual void deserialize(string) = 0;
    virtual string serialize() = 0;
};

#endif //ICT1009_TEAM22_2022_CPP_REPOSITORY_TEMPLATE_H
