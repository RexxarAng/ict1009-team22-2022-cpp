#ifndef ICT1009_TEAM22_2022_CPP_REPOSITORY_EXCEPTION_H
#define ICT1009_TEAM22_2022_CPP_REPOSITORY_EXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

struct ParseNullException : public exception {
    const char * what() const noexcept override {
        return "Unable to parse the datasource's record due to null pointer";
    }
};

struct ParseAttributeMismatchException : public exception {
    const char * what() const noexcept override {
        return "Unable to parse the datasource's record due to mismatch attributes";
    }
};

#endif //ICT1009_TEAM22_2022_CPP_REPOSITORY_EXCEPTION_H
