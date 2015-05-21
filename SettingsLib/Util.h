#ifndef CPP_UTIL_H
#define CPP_UTIL_H

#include <string>

class Util {
public:
    static void assertTrue(const std::string &message, const bool &condition);
    template<class T>
    static void assertEquals(const std::string &message, const T &actual, const T &expected);
    static void assertEquals(const std::string &message, const double &actual, const double &expected);
    static int stringToInt(const std::string &s);
    static bool stringToBool(const std::string &s);
    static double stringToDouble(const std::string &s);
    static std::string intToString(const int &n);
    static std::string boolToString(const bool &n);
    static std::string doubleToString(const double &n);
};


#endif //CPP_UTIL_H
