#pragma once

#include <sstream>
#include <algorithm>
#include "TupleReader.h"
#include "Exceptions.h"

template <typename... Args>
class CSVParser
{
public:
    CSVParser(std::ifstream& file, size_t linesToSkip = 0, char separator = ';', char escapeChar = '"') : _file(file), _linesToSkip(linesToSkip), _separator(separator), _escapeChar(escapeChar)
    {
        skipLines();
        _startingPosition = _file.tellg();
    }

    class Iterator
    {
    public:
        Iterator(CSVParser& parser, bool isEnd) : _parser(parser), _isEnd(isEnd), _lineNumber(parser._linesToSkip + 1), _currentPosition(parser._startingPosition)
        {
            if (isEnd)
            {
                return;
            }
            readTuple();
        }

        ~Iterator() = default;


        bool operator==(const Iterator& other) const {
            // ��������� �� ������� ������� � ��������� _isEnd
            return (_isEnd == other._isEnd) &&
                (_isEnd || (_currentPosition == other._currentPosition));
        }

        bool operator!=(const Iterator& other) const
        {
            return _isEnd != other._isEnd;
        }

        Iterator& operator++()
        {
            readTuple();
            return *this;
        }

        std::tuple<Args...> operator*() const
        {
            return _currentTuple;
        }

    private:
        CSVParser& _parser;
        std::tuple<Args...> _currentTuple;
        bool _isEnd;
        size_t _lineNumber;
        std::streampos _currentPosition;

        class OwnCType : public std::ctype<char>
        {
        private:
            mask _table[table_size];

        public:
            explicit OwnCType(char separator, size_t refs = 0) : std::ctype<char>{ &_table[0], false, refs }
            {
                std::copy_n(classic_table(), table_size, _table);
                _table[' '] = lower;
                _table[separator] = space;
            }
        };

        void readTuple() {
    if (_parser._file.eof()) {
        _isEnd = true;
        return;
    }
    _parser._file.clear();
    _parser._file.seekg(_currentPosition);
    std::string currentLine;
    std::getline(_parser._file, currentLine);

    _currentPosition = _parser._file.tellg();

    // ������������ �������������
    std::string processedLine = processEscaping(currentLine);

    // ��������� �� ������� � ��������� ������������ '\x1E'
    std::istringstream lineParser(processedLine);
    lineParser.imbue(std::locale(std::locale::classic(), new OwnCType('\x1E')));

    try {
        _currentTuple = TupleReader<char, std::char_traits<char>, Args...>::read(lineParser, _lineNumber);
    } catch (...) {
        throw; // ������������ ���������� ����
    }

    ++_lineNumber;
}


        std::string processEscaping(const std::string& input) {
            std::string result;
            bool inEscapeMode = false;

            for (size_t i = 0; i < input.size(); ++i) {
                char c = input[i];

                if (c == _parser._escapeChar) {
                    // ����������� ����� �������������
                    inEscapeMode = !inEscapeMode;
                }
                else if (!inEscapeMode && c == _parser._separator) {
                    // ���� �� �� � ������ ������������� � ��������� �����������,
                    // ��������� ��� ��� ���� (��������� �������)
                    result += '\x1E'; // ����������� ������-����������� ��� ����������� ���������
                }
                else {
                    // ��������� ������ � ���������
                    result += c;
                }
            }

            // ���� ������������� �������� ���������� � ������
            if (inEscapeMode) {
                throw std::runtime_error("Unclosed escape sequence in input line: " + input);
            }

            return result;
        }
    };

    Iterator begin()
    {
        _file.clear();
        _file.seekg(_startingPosition);
        return Iterator(*this, false);
    }

    Iterator end()
    {
        return Iterator(*this, true);
    }

private:
    size_t _linesToSkip;
    std::ifstream& _file;
    char _separator;
    char _escapeChar;
    std::streampos _startingPosition;

    void skipLines()
    {
        for (size_t i = 0; i < _linesToSkip; ++i)
        {
            std::string skippedLine;
            std::getline(_file, skippedLine);
        }
    }
};