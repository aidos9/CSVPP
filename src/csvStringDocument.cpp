#include "../include/csvStringDocument.h"
#include "../include/csvException.h"
#include <vector>
#include <sstream>

namespace CSV{
CSVStringDocument::CSVStringDocument(const std::string& csv_string) : string(csv_string)
{

}

void CSVStringDocument::parse()
{
    CSVRow header_row = CSVRow();
    bool header_row_set = false;
    std::vector<CSVRow> p_rows = std::vector<CSVRow>();
    std::istringstream ss = std::istringstream(string);

    while(ss)
    {
        std::string line = read_line(ss);

        if(contains_not_whitespace(line) && !line.empty())
        {
            CSVRow current_row = parse_row(line);

            if(!header_row_set)
            {
                header_row = current_row;
                header_row_set = true;
            }else{
                if(current_row.count() != header_row.count())
                {
                    throw CSVException("The column count does not match the header.", CSVExceptionType::InvalidColumns);
                }

                p_rows.push_back(current_row);
            }
        }
    }

    header = header_row;
    rows_contents = p_rows;
}
}
