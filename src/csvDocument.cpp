#include "../include/csvDocument.h"
#include "../include/csvException.h"
#include <vector>

namespace CSV {

void CSVDocument::parse()
{

}

CSVDocument::~CSVDocument()
{

}

std::string CSVDocument::read_line(std::istream& stream)
{
    std::string line = "";
    bool terminate = false;
    bool in_quotes = false;

    while(stream)
    {
        if(terminate)
        {
            break;
        }

        char c;
        stream.get(c);

        if(c != '\0')
        {
            if(!in_quotes)
            {
                if(c == '\"')
                {
                    line.push_back(c);
                    in_quotes = true;
                }else if(c == '\n')
                {
                    terminate = true;
                }else if(stream.eof())
                {
                    terminate = true;
                }else{
                    line.push_back(c);
                }
            }else{
                if(c == '\"')
                {
                    line.push_back('"');
                    int p = stream.peek();
                    if(p != std::char_traits<int>::eof())
                    {
                        if(p == '\"')
                        {
                            line.push_back('\"');
                            stream.get();
                        }else{
                            in_quotes = false;
                        }
                    }else{
                        throw CSVException("Unterminated string literal.", CSV::CSVExceptionType::UnterminatedString);
                    }
                }else{
                    line.push_back(c);
                }
            }
        }
    }

    return line;
}

bool CSVDocument::contains_not_whitespace(const std::string& str) const
{
    return str.find_first_not_of(" \t\n\v\f\r\0") != std::string::npos;
}

CSVRow CSVDocument::parse_row(const std::string& line)
{
    CSVRow current_row = CSVRow();
    std::string cell = std::string();
    bool in_quotes = false;

    for(size_t i = 0; i < line.size(); i++)
    {
        if(!in_quotes)
        {
            if(line[i] == ',')
            {
                current_row.add_cell(cell);
                cell = "";
            }else if(line[i] == '\"')
            {
                in_quotes = true;
            }else{
                cell.push_back(line[i]);
            }
        }else{
            if(line[i] == '\"')
            {
                if(i+1 < line.size())
                {
                    if(line[i+1] == '\"')
                    {
                        cell += "\"";
                        i++;
                    }else{
                        in_quotes = false;
                    }
                }else{
                    in_quotes = false;
                }
            }else{
                cell.push_back(line[i]);
            }
        }
    }

    current_row.add_cell(cell);

    return current_row;
}

size_t CSVDocument::rows() const
{
    return rows_contents.size();
}

size_t CSVDocument::columns() const
{
    return header.count();
}

CSVRow CSVDocument::get_header() const
{
    return header;
}

std::string CSVDocument::cell_contents(const size_t& row_index, const size_t& cell_index) const
{
    if(row_index >= rows_contents.size())
    {
        throw CSVException("The specified row index does not exist.", CSVExceptionType::InvalidIndex);
    }

    return row_at_index(row_index).at(cell_index);
}

std::string CSVDocument::cell_contents(const size_t& row_index, const std::string& header_id) const
{
    if(row_index >= rows_contents.size())
    {
        throw CSVException("The specified row index does not exist.", CSVExceptionType::InvalidIndex);
    }

    size_t cell_index;

    if(!header.index_of(header_id, cell_index))
    {
        throw CSVException("The specified id does not exist.", CSVExceptionType::InvalidKey);
    }

    return row_at_index(row_index).at(cell_index);
}

CSVRow CSVDocument::row_at_index(const size_t& row_index) const
{
    if(row_index >= rows_contents.size())
    {
        throw CSVException("The specified row index does not exist.", CSVExceptionType::InvalidIndex);
    }

    return rows_contents[row_index];
}

bool CSVDocument::has_header_key(const std::string& key) const
{
    return header.has_item(key);
}
}
