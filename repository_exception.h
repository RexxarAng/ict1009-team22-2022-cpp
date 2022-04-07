#ifndef ICT1009_TEAM22_2022_CPP_REPOSITORY_EXCEPTION_H
#define ICT1009_TEAM22_2022_CPP_REPOSITORY_EXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

struct ParseException : public runtime_error {

    ParseException(const string& source, const string& errorMessage) :
        runtime_error((source + " : " + errorMessage).c_str()) {}

};

struct ParseFileNotFoundException : public ParseException {

    ParseFileNotFoundException(const string& source, const string& fileName) :
        ParseException(source, "Error parsing datasource due to file '" + fileName + "' not found") {}

};

struct ParseAttributeMismatchException : public ParseException {

    ParseAttributeMismatchException(const string& source, const int expected, const int actual) :
        ParseException(
            source,
            "Error parsing datasource's record due number of attributes is mismatched, expected " +
            to_string(expected) + " but has " + to_string(actual)) {}

};

#endif //ICT1009_TEAM22_2022_CPP_REPOSITORY_EXCEPTION_H
