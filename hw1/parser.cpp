#include "parser.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <stdexcept>

Parser::Parser() {}
Parser::~Parser() {}

bool Parser::is_unary(char c){
    return c == '-';
}
bool Parser::delim(char c) {
	return c == ' ';
}

bool Parser::is_op(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int Parser::priority(char op) {
	if (op < 0) { //unary operation
        return 4; // op == -'+' || op == -'-'
	} else if (op == '+' || op == '-') {
        return 1;
	} else if (op == '*' || op == '/' || op == '%') {
        return 2;
	} else {
	    return -1;
	}
}

void Parser::process_op(vector<int>& st, char op) {
	if (op < 0) {
		int l = st.back();  st.pop_back();
		switch (-op) {
			case '+':  st.push_back (l);  break;
			case '-':  st.push_back (-l);  break;
			default: throw runtime_error("invalid operation"); break;
		}
	}
	else {
		int r = st.back();  st.pop_back();
		int l = st.back();  st.pop_back();
		switch (op) {
			case '+':  st.push_back (l + r);  break;
			case '-':  st.push_back (l - r);  break;
			case '*':  st.push_back (l * r);  break;
			case '/':  st.push_back (l / r);  break;
			case '%':  st.push_back (l % r);  break;
			default: throw runtime_error("invalid operation"); break;
		}
	}
}


Parser::result Parser::parse(const string s){
    bool may_unary = true;
	vector<int> st;
	vector<char> op;
	for (size_t i = 0; i < s.length(); ++i) {
        if (delim(s[i])) {
            continue;
		}
		if (s[i] == '(') {
            op.push_back('(');
            may_unary = true;
        }
        else if (s[i] == ')') {
            while (op.back() != '(') {
                process_op(st, op.back()),  op.pop_back();
            }
            op.pop_back();
            may_unary = false;
        }
        else if (is_op(s[i])) {
            char curop = s[i];
            if (may_unary && is_unary(curop)) {
                curop = -curop;
            }
            while (!op.empty() &&
                   (curop >= 0 && priority(op.back()) >= priority(curop) ||
                    curop < 0 && priority(op.back()) > priority(curop))) {
                            process_op(st, op.back()),  op.pop_back();
                    }
            op.push_back(curop);
            may_unary = true;
        } else {
            string operand;
            while (i < s.length() && isalnum(s[i])) {
                operand += s[i++];
            }
            --i;
            if (isdigit(operand[0])) {
                st.push_back (atoi(operand.c_str()));
            } else {
                throw runtime_error("operand is not a number");
            }
            may_unary = false;
        }
	}
	while (!op.empty()) {
        process_op (st, op.back());
        op.pop_back();
	}

	if (st.size() > 1) {
        throw runtime_error("wrong input");
	}

	return st.back();
}
