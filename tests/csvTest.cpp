#include "../include/csv.h"
#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("[CSV-Parse-Import]") {
   CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,jane,\"t-mart\tbob,\"\n\"bob,,,\",,\"t-mart\tbob\"\n");
   parser.parse();
}

TEST_CASE("[CSV-Header-Import]") {
   CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,jane,\"t-mart\tbob,\"\n\"bob,,,\",,\"t-mart\tbob\"\n");
   parser.parse();
   auto header = parser.get_header();

   REQUIRE(header.at(0) == "name");
   REQUIRE(header.at(1) == "job");
   REQUIRE(header.at(2) == "location");
}

TEST_CASE("[CSV-ID-Selection-Import]") {
    CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,mechanic,australia\njames,tech,america\n");
    parser.parse();

    REQUIRE(parser.cell_contents(0, "name") == "bob");
    REQUIRE(parser.cell_contents(0, "job") == "mechanic");
    REQUIRE(parser.cell_contents(0, "location") == "australia");

    REQUIRE(parser.cell_contents(1, "name") == "james");
    REQUIRE(parser.cell_contents(1, "job") == "tech");
    REQUIRE(parser.cell_contents(1, "location") == "america");
}

TEST_CASE("[CSV-Plain-Import]") {
    CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,mechanic,australia\njames,tech,america\n");
    parser.parse();
    std::vector<std::vector<std::string>> comparison = {{"bob","mechanic","australia"}, {"james", "tech", "america"}};

    for(size_t r = 0; r < parser.rows(); r++)
    {
        for(size_t c = 0; c < parser.columns(); c++)
        {
            REQUIRE(parser.row_at_index(r).at(c) == comparison[r][c]);
        }
    }
}

TEST_CASE("[CSV-Blank-Import]") {
    CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,mechanic,australia\njames,,america\n");
    parser.parse();
    std::vector<std::vector<std::string>> comparison = {{"bob","mechanic","australia"}, {"james", "", "america"}};

    for(size_t r = 0; r < parser.rows(); r++)
    {
        for(size_t c = 0; c < parser.columns(); c++)
        {
            REQUIRE(parser.row_at_index(r).at(c) == comparison[r][c]);
        }
    }
}

TEST_CASE("[CSV-NewLines-Import]") {
    CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,mechanic,australia\njames,\"tech\n in\n industry\",america\n");
    parser.parse();
    std::vector<std::vector<std::string>> comparison = {{"bob","mechanic","australia"}, {"james", "tech\n in\n industry", "america"}};

    for(size_t r = 0; r < parser.rows(); r++)
    {
        for(size_t c = 0; c < parser.columns(); c++)
        {
            REQUIRE(parser.row_at_index(r).at(c) == comparison[r][c]);
        }
    }
}

TEST_CASE("[CSV-Quotes-Import]") {
    CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,mechanic,australia\njames,\"tech \"\"in\"\" industry\",america\n");
    parser.parse();
    std::vector<std::vector<std::string>> comparison = {{"bob","mechanic","australia"}, {"james", "tech \"in\" industry", "america"}};

    for(size_t r = 0; r < parser.rows(); r++)
    {
        for(size_t c = 0; c < parser.columns(); c++)
        {
            REQUIRE(parser.row_at_index(r).at(c) == comparison[r][c]);
        }
    }
}

TEST_CASE("[CSV-File]") {
    std::ifstream fs = std::ifstream();
    fs.open("test.csv");
    CSV::CSVStreamDocument doc = CSV::CSVStreamDocument(fs);
    doc.parse();

    std::vector<std::vector<std::string>> comparison = {{"bob","\"tennis\"","hawaii"},{"james","june","New York"}};

    for(size_t r = 0; r < doc.rows(); r++)
    {
        for(size_t c = 0; c < doc.columns(); c++)
        {
            REQUIRE(doc.row_at_index(r).at(c) == comparison[r][c]);
        }
    }
}

TEST_CASE("[CSV-Serialize]") {
    CSV::CSVStringDocument parser = CSV::CSVStringDocument("name,job,location\nbob,mechanic,australia\njames,\"tech \"\"in\"\" industry\",america\n");
    parser.parse();

    REQUIRE(parser.to_string() == "name,job,location\nbob,mechanic,australia\njames,\"tech \"\"in\"\" industry\",america\n");
}
