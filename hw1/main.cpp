#include <iostream>
#include "parser.h"
#include <cassert>

using namespace std;

int main()
{
    try {
        Parser* p = new Parser();   //new - указатель

        cout << "TESTING...\n\n";

        /* TEST 1 */
        assert(p->parse("10") == 10);   //p->meth(val) == (*p).meth(val)
        cout << "TEST1 - OK\n";

        /*TEST 2 */
        assert(p->parse("20") == 20);
        cout << "TEST2 - OK\n";

        /*TEST 3 */
        assert(p->parse("(-2 + 3)*5") == 5);
        cout << "TEST3 - OK\n";

        cout << "\nYOUR INPUT\n\n";

        string s;   //локальные переменные(стек) new(куча)
        while(getline(cin, s)) {
            cout << p->parse(s) << endl;
        }

        delete p;   // вызвать деструктор
    } catch(exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    return 0;
}
