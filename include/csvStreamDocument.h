#ifndef CSVSTREAMDOCUMENT_H
#define CSVSTREAMDOCUMENT_H

#include "csvDocument.h"

namespace CSV {
class CSVStreamDocument : public CSVDocument
{
public:
    CSVStreamDocument(std::istream& stream);

    void parse() override;

private:
    std::istream& reading_stream;
};
}

#endif // CSVSTREAMDOCUMENT_H
