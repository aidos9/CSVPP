#ifndef CSV_DOCUMENT_H
#define CSV_DOCUMENT_H

#include "csvRow.h"
#include <string>
#include <istream>
#include <sstream>
#include <ostream>

namespace CSV {
class CSVDocument
{
public:
    virtual void parse();
    virtual ~CSVDocument();

    size_t rows() const;
    size_t columns() const;

    void append_row(const CSVRow& row);
    void remove_row(const size_t& row_index);

    std::string cell_contents(const size_t& row_index, const size_t& cell_index) const;
    std::string cell_contents(const size_t& row_index, const std::string& header_id) const;

    CSVRow row_at_index(const size_t& row_index) const;
    CSVRow get_header() const;
    void set_header(const CSVRow& row); // Clears all the rows!

    bool has_header_key(const std::string& key) const;

    std::string to_string() const;
    void write_stream(std::ostream& stream) const;

protected:
    std::string read_line(std::istream& stream);
    CSVRow parse_row(const std::string& line);
    bool contains_not_whitespace(const std::string& str) const;
    bool contains_whitespace(const std::string& str) const;
    std::string serialize_row(const CSVRow& row) const;

    CSVRow header;
    std::vector<CSVRow> rows_contents;
};
}

#endif // CSV_DOCUMENT_H
