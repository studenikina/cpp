#include <string>
#include <iostream>
#include "settings.h"

using namespace std;

int main(int argc, char* argv[]) {
    settings settings1("../files/settings.txt");
    settings1.reset();
    settings1.reload();
    vector <string> params = {"first_name", "second_name", "age"};
    vector <string> new_values = {};
    cout << "file: settings.txt\n\n";
    for(vector<string>::iterator i = params.begin(), nv = new_values.begin(); i != params.end(); i++) {
        cout << *i << " = " << settings1.get(*i, "-") << "\n";
        if (nv != new_values.end()){
            settings1.set(*i, *nv);
            cout << *i << " = " << settings1.get(*i, "-") << "\n";
            nv++;
        }
    }

    return 0;
};
