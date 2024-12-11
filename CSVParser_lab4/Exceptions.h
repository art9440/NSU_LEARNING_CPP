#pragma once

#include <iostream>
#include <string>

class ErrorHandler : public std::exception
{
private:
    std::string _text;

public:
    ErrorHandler(std::string text) : _text{ text } {}

    const char* what() const noexcept
    {
        return _text.c_str();
    }
};

class NotEnoughData : public ErrorHandler
{
    size_t _lineNumber;

public:
    NotEnoughData(size_t lineNumber) : _lineNumber{ lineNumber }, ErrorHandler{ "Not enough data! " } {};
    size_t getLineNumber() const { return _lineNumber; }
};

class FailedToReadData : public ErrorHandler
{
    size_t _lineNumber;
    size_t _columnNumber;

public:
    FailedToReadData(size_t lineNumber, size_t columnNumber) : _lineNumber{ lineNumber }, _columnNumber{ columnNumber }, ErrorHandler{ "Failed to read data! " } {};
    size_t getLineNumber() const { return _lineNumber; }
    size_t getColumnNumber() const { return _columnNumber; }
};