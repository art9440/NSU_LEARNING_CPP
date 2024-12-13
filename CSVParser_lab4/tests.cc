#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "CsvParser.h"
#include "TuplePrinter.h"

// ��������������� ������� ��� �������� ���������� �����
void createTemporaryFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to create temporary file: " + filename);
    }
    file << content;
    file.close();
}

// ���� �������� ��������
TEST(CSVParserTest, BasicParsing) {
    std::string filename = "test_basic_parsing.csv";
    createTemporaryFile(filename, "1,John,25\n2,Alice,30\n3,Bob,40");

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open()) << "Failed to open the test file: " << filename;

    CSVParser<int, std::string, int> parser(file, 0, ',');

    auto it = parser.begin();
    ASSERT_NE(it, parser.end());
    EXPECT_EQ(*it, std::make_tuple(1, "John", 25)); ++it;
    ASSERT_NE(it, parser.end());
    EXPECT_EQ(*it, std::make_tuple(2, "Alice", 30)); ++it;
    ASSERT_NE(it, parser.end());
    EXPECT_EQ(*it, std::make_tuple(3, "Bob", 40)); ++it;
    EXPECT_EQ(it, parser.end());

    file.close();
}

// ���� �������� �����
TEST(CSVParserTest, SkipLines) {
    std::string filename = "test_skip_lines.csv";
    createTemporaryFile(filename, "Header1,Header2,Header3\n1,John,25\n2,Alice,30");

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open()) << "Failed to open the test file: " << filename;

    CSVParser<int, std::string, int> parser(file, 1, ',');

    auto it = parser.begin();
    ASSERT_NE(it, parser.end());
    EXPECT_EQ(*it, std::make_tuple(1, "John", 25)); ++it;
    ASSERT_NE(it, parser.end());
    EXPECT_EQ(*it, std::make_tuple(2, "Alice", 30)); ++it;
    EXPECT_EQ(it, parser.end());

    file.close();
}

// ���� ��������� �������������
TEST(CSVParserTest, Escaping) {
    std::string filename = "test_escaping.csv";
    createTemporaryFile(filename, "1,\"John, Smith\",25\n2,\"Alice, Johnson\",30");

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open()) << "Failed to open the test file: " << filename;

    CSVParser<int, std::string, int> parser(file, 0, ',');

    auto it = parser.begin();
    ASSERT_NE(it, parser.end());
    EXPECT_EQ(*it, std::make_tuple(1, "John, Smith", 25)); ++it;
    ASSERT_NE(it, parser.end());
    EXPECT_EQ(*it, std::make_tuple(2, "Alice, Johnson", 30)); ++it;
    EXPECT_EQ(it, parser.end());

    file.close();
}

TEST(CSVParserTest, NotEnoughData) {
    std::string filename = "test_not_enough_data.csv";
    createTemporaryFile(filename, "Header1;Header2;Header3;Header4\n1;John;25\n2;Alice"); // ������ 2 �������� ������������ ������

    std::ifstream file_stream(filename);
    ASSERT_TRUE(file_stream.is_open()) << "Failed to open the test file: " << filename;

    CSVParser<int, std::string, double, int> parser(file_stream, 1, ';', '"'); // ���������� ���������

    try {
        for (auto tuple : parser) {
            FAIL() << "Expected NotEnoughData exception";
        }
    }
    catch (const NotEnoughData& e) {
        EXPECT_EQ(e.getLineNumber(), 2); // ���������, ��� ���������� ������������� ��� ������ ������
    }
    catch (...) {
        FAIL() << "Expected NotEnoughData exception, but got a different exception";
    }

    file_stream.close();
}

TEST(CSVParserTest, FailedToReadData) {
    std::string filename = "test_failed_to_read.csv";
    createTemporaryFile(filename, "Header1;Header2;Header3\n1;John;25\n2;Alice;not_a_number");

    std::ifstream file_stream(filename);
    ASSERT_TRUE(file_stream.is_open());

    CSVParser<int, std::string, double> parser(file_stream, 1, ';', '"');

    try {
        for (auto tuple : parser) {
            std::cout << tuple << std::endl;
            
        }
    }
    catch (const FailedToReadData& e) {
        EXPECT_EQ(e.getLineNumber(), 3);
        EXPECT_EQ(e.getColumnNumber(), 3);
    }
    catch (...) {
        FAIL() << "Expected FailedToReadData exception, but got a different exception";
    }

    file_stream.close();
}

TEST(CSVParserTest, ParsingWithEscapedQuotes) {
    // �������� ���������� ����� � ��������������� ���������
    std::string filename = "test_parsing_with_escaped_quotes.csv";
    createTemporaryFile(filename,
        "1;\"John \"\"Doe\"\"\";25;\"New York\";3.5\n"
        "2;\"Alice \"\"Smith\"\"\";30;\"Los Angeles\";4.0");

    // �������� �����
    std::ifstream file_stream(filename);
    ASSERT_TRUE(file_stream.is_open()) << "Failed to open the test file: " << filename;

    // �������� �������
    CSVParser<size_t, std::string, int, std::string, double> parser(file_stream, 0, ';', '"');

    // ��������, ��� �������������� ������� ���������� ���������
    for (auto tuple : parser) {
        std::string field = std::get<1>(tuple); // ���� �� ������� (������ �������)
        EXPECT_TRUE(field.find('"') == std::string::npos)
            << "Field contains unexpected quotes: " << field;
    }

    file_stream.close();
}


