#ifndef CSVEXCEPTION_H
#define CSVEXCEPTION_H

#include <stdexcept>
#include <string>

namespace CSV {
enum CSVExceptionType {
    InvalidKey,
    InvalidIndex,
    InvalidColumns,
    UnterminatedString
};

class CSVException : public std::runtime_error
{
public:
    explicit CSVException(const std::string& description, const CSVExceptionType& type);

    CSVExceptionType type() const;
    std::string description() const;

private:
    CSVExceptionType exception_type;
    std::string exception_description;
};
}

#endif // CSVEXCEPTION_H
