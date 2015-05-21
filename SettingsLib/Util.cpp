#ifndef _UTIL_H_
#define _UTIL_H_

#include "Util.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <stdexcept>

void Util::assertTrue(const std::string &message, const bool &condition) {
    if (!condition) {
        std::cerr << message << "\n";
    }
}

template<class T>
void Util::assertEquals(const std::string &message, const T &actual, const T &expected) {
    std::ostringstream stream;
    stream << message << ": Expected " << expected << ", found " << actual;
    assertTrue(stream.str(), actual == expected);
}

void Util::assertEquals(const std::string &message, const double &actual, const double &expected) {
    std::ostringstream stream;
    stream << message << ": Expected " << expected << ", found " << actual;
    assertTrue(stream.str(), std::abs(actual - expected) < 1e-9);
}

int Util::stringToInt(const std::string &s) {
    std::istringstream stream(s);
    int ans;
    stream >> ans;

    return ans;
}

bool Util::stringToBool(const std::string &s) {
    if (s == "true") {
        return true;
    }
    if (s == "false") {
        return false;
    }
    throw std::runtime_error("Wrong value: " + s);
}

double Util::stringToDouble(const std::string &s) {
    std::istringstream stream(s);
    double ans;
    stream >> ans;

    return ans;
}

std::string Util::intToString(const int &n) {
    std::ostringstream stream;
    stream << n;

    return stream.str();
}

std::string Util::boolToString(const bool &n) {
    return n ? "true" : "false";
}

std::string Util::doubleToString(const double &n) {
    std::ostringstream stream;
    stream << n;

    return stream.str();
}

#endif //_UTIL_H_