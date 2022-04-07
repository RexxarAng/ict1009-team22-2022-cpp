#ifndef ICT1009_TEAM22_2022_CPP_HELPER_H
#define ICT1009_TEAM22_2022_CPP_HELPER_H

//helper function to parse CSV file with commas and quotes
enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};

std::vector<std::string> readCSVRow(const std::string &row, char separator = ',') {
    CSVState state = CSVState::UnquotedField;
 
    std::vector<std::string> fields {""};
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
                              break; }
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
#endif
