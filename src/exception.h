#pragma once
#include <string>
using std::string;

struct ConvertorException : public std::exception {
    ConvertorException(const char* text) : message(text) {}
    ConvertorException(const string& text) : message(text.c_str()) {}
    const char* what() const noexcept {
        return message;
    }
    const char* message;
};