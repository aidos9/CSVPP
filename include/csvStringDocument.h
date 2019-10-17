#ifndef CSVSTRINGDOCUMENT_H
#define CSVSTRINGDOCUMENT_H

#include "csvDocument.h"

namespace CSV {
class CSVStringDocument : public CSVDocument
{
public:
    CSVStringDocument();
    CSVStringDocument(const std::string& csv_string);

    void parse() override;
private:
    std::string string;
};
}

#endif // CSVSTRINGDOCUMENT_H
