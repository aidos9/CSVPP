#ifndef CSV_DOCUMENT_H
#define CSV_DOCUMENT_H

#include "csvRow.h"
#include <string>
#include <istream>
#include <sstream>

namespace CSV {
class CSVDocument
{
public:
    virtual void parse();
    virtual ~CSVDocument();

    size_t rows() const;
    size_t columns() const;

    std::string cell_contents(const size_t& row_index, const size_t& cell_index) const;
    std::string cell_contents(const size_t& row_index, const std::string& header_id) const;

    CSVRow row_at_index(const size_t& row_index) const;
    CSVRow get_header() const;

    bool has_header_key(const std::string& key) const;

protected:
    std::string read_line(std::istream& stream);
    CSVRow parse_row(const std::string& line);
    bool contains_not_whitespace(const std::string& str) const;

    CSVRow header;
    std::vector<CSVRow> rows_contents;
};
}

#endif // CSV_DOCUMENT_H
