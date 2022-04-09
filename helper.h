#ifndef ICT1009_TEAM22_2022_CPP_HELPER_H
#define ICT1009_TEAM22_2022_CPP_HELPER_H
#include <string>
#include <vector>

using namespace std;

//helper function to parse CSV file with commas and quotes
enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};

class CSVReader {
public:
    static vector<string> readCSVRow(const string& row, char separator = ',');
};


#endif
