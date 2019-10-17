#include "../include/csvDocument.h"
#include "../include/csvException.h"
#include <vector>
#include <iostream>

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

bool CSVDocument::contains_whitespace(const std::string& str) const
{
    return str.find_first_of(" \t\n\v\f\r\0") != std::string::npos;
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

void CSVDocument::set_header(const CSVRow& row)
{
    header = row;
    rows_contents.clear();
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

std::string CSVDocument::serialize_row(const CSVRow& row) const
{
    std::string result = "";
    size_t i = 0;

    for(i = 0; i < row.count()-1; i++)
    {
        std::string item = row.at(i);

        if(item.find('"') != std::string::npos)
        {
            for(size_t c = 0; c < item.size(); c++)
            {
                if(item[c] == '"')
                {
                    item.insert(c, "\"");
                    c++;
                }
            }
        }

        if(contains_whitespace(item))
        {
            item.insert(0, "\"");
            item.insert(item.size(), "\"");
        }

        result += item+",";
    }

    std::string item = row.at(i);

    if(item.find('"') != std::string::npos)
    {
        for(size_t c = 0; c < item.size(); c++)
        {
            if(item[c] == '"')
            {
                item.insert(c, "\"");
                c++;
            }
        }
    }

    if(contains_whitespace(item))
    {
        item.insert(0, "\"");
        item.insert(item.size(), "\"");
    }

    result += item;
    result += "\n";

    return result;
}

std::string CSVDocument::to_string() const
{
    std::string output = serialize_row(header);

    for(size_t r = 0; r < rows(); r++)
    {
        output += serialize_row(row_at_index(r));
    }

    return output;
}

void CSVDocument::write_stream(std::ostream& stream) const
{
    for(size_t r = 0; r < rows(); r++)
    {
        stream << serialize_row(row_at_index(r));
    }
}

void CSVDocument::append_row(const CSVRow& row)
{
    rows_contents.push_back(row);
}

void CSVDocument::remove_row(const size_t& row_index)
{
    if(row_index < rows())
    {
        rows_contents.erase(rows_contents.begin() + row_index);
    }
}

}
