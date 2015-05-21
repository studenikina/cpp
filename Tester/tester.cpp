#include <assert.h>
#include "../SettingsLib/settings.h"

using namespace std;

class tester {
public:
    typedef void(*test_function)();
    typedef pair <string, test_function> test;

    tester() {}
    int run(void(*test)()) {
        int start = clock();
        test();
        int end = clock();
        return end - start;
    }
    void runner(vector <test> tests, bool interrupt = true) {
        int duration;
        pair <int, int> max_duration(0, 0);
        for(int i = 0; i < (int)tests.size(); i++) {
            printf("TEST %20s ... ", tests[i].first.c_str());
            try {
                duration = run(tests[i].second);
                printf("OK\n");

                if (duration > max_duration.first) {
                    max_duration = make_pair(duration, i);
                }
            } catch (exception& e) {
                printf("\n  Exception: %s\n", e.what());
            }
            printf("==== %.3lf s.\n\n", 1.0*duration/1000000);
        }
    }
};

void test_profile_settings() {
    settings profile("../Tester/files/profile.txt");
    assert(profile.get("first_name","") == "Elizaveta");
    assert(profile.get("second_name","") == "Studenikina");
    assert(int(profile["age"]) == 19);
    assert(bool(profile["loves_cpp"]) == true);

    /*actions */

    profile.set("university", "MSU");
    assert(profile.get("university", "") == "MSU");
}

void test_random_settings() {
    settings random("../Tester/files/random.txt");
    vector <string> s = {
            "journey",
            "chamber",
            "way",
            "yet",
            "females",
            "man",
            "extensive",
            "and",
            "dejection",
            "get",
            "delivered",
            "deficient",
            "sincerity",
            "gentleman",
            "age",
            "end",
            "instrument",
            "possession",
            "contrasted",
            "motionless"
    };
    for(int i = 0; i < (int)s.size(); i++) {
        assert(random.get(s[i], "") == s[i]);
    }
}

void test_big_settings() {
    settings big("../Tester/files/big.txt");

    vector <string> options;
    int MAX_OPTIONS = 2015;
    int THREAD_COUNT = 4;
    for(int t = 0; t < THREAD_COUNT; t++) {
        for(int i = 0; i < MAX_OPTIONS; i++) {
            string s = "thread" + std::to_string(t + 1) + "_option" + std::to_string(i + 1);
            options.push_back(s);
        }
    }
    for(int i = 0; i < (int)options.size(); i++) {
        assert(big.get(options[i], "") == "");
    }
}


int main() {
    vector <tester::test> tests = {
            {"profile", test_profile_settings},
            {"random", test_random_settings},
            {"big", test_big_settings}
    };
    tester t;
    t.runner(tests);
    return 0;
}
