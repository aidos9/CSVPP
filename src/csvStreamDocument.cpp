#include "../include/csvStreamDocument.h"
#include "../include/csvException.h"
#include <vector>

namespace CSV {
CSVStreamDocument::CSVStreamDocument(std::istream& stream) : reading_stream(stream)
{

}

void CSVStreamDocument::parse()
{
    CSVRow header_row = CSVRow();
    bool header_row_set = false;
    std::vector<CSVRow> p_rows = std::vector<CSVRow>();

    while(reading_stream)
    {
        std::string line = read_line(reading_stream);

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
