#include "helper.h"

vector<string> CSVReader::readCSVRow(const string& row, char separator) {
    CSVState state = CSVState::UnquotedField;

    vector<string> fields{ "" };
    size_t i = 0; // index of the current field

    for (char c : row) {
        switch (state) {
        case CSVState::UnquotedField:
            if (c == separator) {
                fields.push_back(""); i++;
            }
            else if (c == '"') {
                state = CSVState::QuotedField;
            }
            else {
                fields[i].push_back(c);
            }
            break;
        case CSVState::QuotedField:
            switch (c) {
            case '"': state = CSVState::QuotedQuote;
                break;
            default:  fields[i].push_back(c);
                break;
            }
            break;
        case CSVState::QuotedQuote:
            if (c == separator) {
                fields.push_back(""); i++;
                state = CSVState::UnquotedField;
            }
            else if (c == '"') {
                fields[i].push_back('"');
                state = CSVState::QuotedField;
            }
            else {
                state = CSVState::UnquotedField;
            }

            break;
        }
    }
    return fields;
}