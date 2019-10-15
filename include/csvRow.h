#ifndef CSVROW_H
#define CSVROW_H

#include <vector>
#include <string>

namespace CSV {
class CSVRow
{
public:
    CSVRow();
    CSVRow(const std::vector<std::string>& cells);

    void add_cell(const std::string& cell);
    std::string at(const size_t& index) const;
    size_t count() const;
    bool index_of(const std::string& id, size_t& index) const;
    bool has_item(const std::string& id) const;

private:
    std::vector<std::string> cells;
};
}

#endif // CSVROW_H
