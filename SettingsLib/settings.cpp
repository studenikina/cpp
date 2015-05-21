#include <iostream>
#include <fstream>
#include "settings.h"
#include <algorithm>
#include "Util.h"

using namespace std;

/* Class Settings functions */

settings::settings(const char * filename) {
    this->filename = string(filename);
    params = parse_file(this->filename);
    //params.push_back(param::param_ptr(new param("name", "Liza")));
}

settings::settings(std::string const &filename) {
    this->filename = filename;
    params = parse_file(this->filename);
}

std::string const& settings::get(std::string const &name, const string &def) const {
    try {
        return find_by_name(name).value;
    } catch (...) {
        return def;
    }
}

void settings::set(std::string const &name, std::string const &value) {
    find_by_name(name) = value;
}

void settings::reset() {
    params.clear();
}

void settings::reload() {
    params = parse_file(this->filename);
}

/*
 * Returns const instance of param class. Throws std::runtime_exception
 */
const settings::param settings::operator[](std::string const &name) const {
    return settings::param(find_by_name(name));
}

/*
 * Safely returns instance of param class
 */
settings::param settings::operator[](std::string const &name) {
    try {
        return settings::param(find_by_name(name));
    } catch (...) {
        return settings::param(name, "");
    }
}

/* Class Settings private functions */

vector<settings::param::param_ptr> settings::parse_file(std::string const &filename) {
    std::ifstream infile(this->filename);
    std::string line;
    vector<param::param_ptr> tmp;
    while (std::getline(infile, line)) {
        line.erase(remove_if(line.begin(), line.end(), (int(*)(int))isspace), line.end());
        if (line.empty() || line.at(0) == '#') {
            continue;
        } else {
            size_t pos = line.find('=');
            if (pos == string::npos) {
                continue;
            } else {
                string name = line.substr(0, pos), value;
                if (pos + 1 < line.size() && line.at(pos + 1) == '"') {
                    if (pos + 1 < line.size() - 1 && line.back() == '"') {
                        size_t len = line.size() - 2 - (pos + 2) + 1;
                        value = line.substr(pos + 2, len);
                    }
                } else {
                    if (pos + 1 < line.size()) {
                        value = line.substr(pos + 1);
                    }
                }
                tmp.push_back(param::param_ptr(new param(name, value)));
            }
        }
    }
    return tmp;
}

settings::param &settings::find_by_name(std::string const &name) const {
    for(vector<param::param_ptr>::const_iterator i = params.begin(); i != params.end(); i++) {
        if ((*i)->name == name) {
            return *(*i);
        }
    }
    throw std::runtime_error("no param with such name = "+name);
}


/* Class Param functions */

settings::param::param(std::string const &name, std::string const &value)
        : name(name),
          value(value) {

}

settings::param::param(const settings::param::param_ptr &other)
        : name(other->name),
          value(other->value) {

}

settings::param::param(const settings::param &other)
        : name(other.name),
          value(other.value) {

}

settings::param::operator std::string() const {
    return value;
}

settings::param::operator int() const {
    return Util::stringToInt(value);
}

settings::param::operator bool() const {
    return Util::stringToBool(value);
}

settings::param::operator double() const {
    return Util::stringToDouble(value);
}

settings::param &settings::param::operator=(const string &conststring) {
    value = conststring;
    return *this;
}

settings::param &settings::param::operator=(int i) {
    value = Util::intToString(i);
    return *this;
}

settings::param &settings::param::operator=(bool b) {
    value = Util::boolToString(b);
    return *this;
}

settings::param &settings::param::operator=(double d) {
    value = Util::doubleToString(d);
    return *this;
}

settings::param &settings::param::operator+=(const string &conststring) {
    value += conststring;
    return *this;
}

settings::param &settings::param::operator+=(int i) {
    value = Util::intToString(Util::stringToInt(value) + i);
    return *this;
}

settings::param &settings::param::operator+=(double d) {
    value = Util::doubleToString(Util::stringToDouble(value) + d);
    return *this;
}

settings::param &settings::param::operator-=(int i) {
    value = Util::intToString(Util::stringToInt(value) - i);
    return *this;
}

settings::param &settings::param::operator-=(double d) {
    value = Util::doubleToString(Util::stringToDouble(value) - d);
    return *this;
}

settings::param &settings::param::operator*=(int i) {
    value = Util::intToString(Util::stringToInt(value) * i);
    return *this;
}

settings::param &settings::param::operator*=(double d) {
    cout << "atata\n";
    value = Util::doubleToString(Util::stringToDouble(value) * d);
    cout << value << endl;
    return *this;
}

settings::param &settings::param::operator/=(int i) {
    if (i == 0) {
        throw new runtime_error("division by zero");
    }
    value = Util::intToString(Util::stringToInt(value) / i);
    return *this;
}

settings::param &settings::param::operator/=(double d) {
    if (d < 1e-15) {
        throw new runtime_error("division by zero");
    }
    value = Util::doubleToString(Util::stringToDouble(value) / d);
    return *this;
}

settings::param &settings::param::operator|=(bool b) {
    value = Util::boolToString(Util::stringToBool(value) | b);
    return *this;
}

settings::param &settings::param::operator&=(bool b) {
    value = Util::boolToString(Util::stringToBool(value) & b);
    return *this;
}

bool settings::param::is_empty() const {
    return (value == "");
}
