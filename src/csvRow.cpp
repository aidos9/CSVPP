#include "../include/csvRow.h"
#include "../include/csvException.h"
#include <algorithm>

namespace CSV {
CSVRow::CSVRow()
{

}

CSVRow::CSVRow(const std::vector<std::string>& cells) : cells(cells)
{

}

void CSVRow::add_cell(const std::string& cell)
{
    cells.push_back(cell);
}

std::string CSVRow::at(const size_t& index) const
{
    if(index >= cells.size())
    {
        throw CSVException("The specified column index does not exist.", CSVExceptionType::InvalidIndex);
    }

    return cells[index];
}

size_t CSVRow::count() const
{
    return cells.size();
}

bool CSVRow::index_of(const std::string &id, size_t &index) const
{
    auto it_distance = std::find(cells.begin(), cells.end(), id);
    if(it_distance == cells.end())
    {
        return false;
    }else{
        index = std::distance(cells.begin(), it_distance);
        return true;
    }
}

bool CSVRow::has_item(const std::string& id) const
{
    auto it_distance = std::find(cells.begin(), cells.end(), id);
    return it_distance != cells.end();
}
}
