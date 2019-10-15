#include "../include/csvException.h"

namespace CSV {
CSVException::CSVException(const std::string& description, const CSVExceptionType& type) : std::runtime_error(description),
    exception_type(type), exception_description(description)
{

}

CSVExceptionType CSVException::type() const
{
    return exception_type;
}

std::string CSVException::description() const
{
    return exception_description;
}
}
