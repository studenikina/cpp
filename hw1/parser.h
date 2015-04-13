#ifndef PARSER_H

#define PARSER_H

#include <string>
#include <vector>

using namespace std;

struct Parser {
public:
    typedef int result;
    Parser();// конструктор
    ~Parser();//деструктор
    result parse(const string s);//ссылка на строку которую нельзя менять внутри этого метода
private:
    bool is_unary(char c);
    bool delim (char c);
    bool is_op (char c);
    int priority (char op);
    void process_op (vector<int> & st, char op);
    int calc(string & s);
    result str_to_num(const string& s);
};

#endif // PARSER_H
