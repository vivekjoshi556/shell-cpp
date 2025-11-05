#pragma once

#include <stdexcept>

class ExitException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Shell exit requested";
    }
};
