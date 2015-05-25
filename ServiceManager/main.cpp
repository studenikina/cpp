#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
#include "service_manager.h"
#include "writer_service.h"
#include <functional>
#include <unistd.h>

using namespace std;

const int MAX_OPTIONS = (int)4e3;
const int THREAD_COUNT = 4;
const char* PATH = "../files/threads.txt";

void generate_settings(vector<string>& options, int thread_count = THREAD_COUNT, int options_max = MAX_OPTIONS) {
    FILE *f = nullptr;
    try {
        f = fopen(PATH, "w");
        string s, prefix;
        char tmp[10];
        for(int t = 0; t < thread_count; t++) {
            for(int i = 0; i < options_max; i++) {
                prefix = "thread" + std::to_string(t + 1) + "_option" + std::to_string(i + 1);
                s = prefix + "=\"\"\n"; //threadXXX_optionYYYYYY=""
                options.push_back(prefix);
                fputs(s.c_str(), f);
            }
        }
        fclose(f);
    } catch(exception& e) {
        cerr << "File: " << e.what() << endl;
        if (f != nullptr) {
            fclose(f);
        }
    }
}

int main() {

    try {
        vector <string> options; // stores generated options
        generate_settings(options); //generate file with settings

        std::shared_ptr<settings> m_settings(new settings(PATH));
        std::shared_ptr<service_manager> m_service_manager(new service_manager(m_settings));

        std::shared_ptr<writer_service> t1(new writer_service(1, MAX_OPTIONS, "thread1"));
        std::shared_ptr<writer_service> t2(new writer_service(2, MAX_OPTIONS, "thread2"));
        std::shared_ptr<writer_service> t3(new writer_service(3, MAX_OPTIONS, "thread3"));
        std::shared_ptr<writer_service> t4(new writer_service(4, MAX_OPTIONS, "thread4"));
        //std::shared_ptr<writer_service> t5(new writer_service(5, MAX_OPTIONS, "thread5"));
        //std::shared_ptr<writer_service> t6(new writer_service(6, MAX_OPTIONS, "thread6"));

        t1->setup(m_settings, m_service_manager);
        t2->setup(m_settings, m_service_manager);
        t3->setup(m_settings, m_service_manager);
        t4->setup(m_settings, m_service_manager);
        //t5->setup(m_settings, m_service_manager);
        //t6->setup(m_settings, m_service_manager);

        m_service_manager->run_service(t1);
        m_service_manager->run_service(t2);
        m_service_manager->run_service(t3);
        m_service_manager->run_service(t4);
        //m_service_manager->run_service(t5);
        //m_service_manager->run_service(t6);

        auto process_indicator = [&]()->void{

            if (m_service_manager->get_count() + 10*THREAD_COUNT >= (int)options.size()) {
                m_service_manager->set_running(false);
            }
            std::cout << "Processing: " << m_service_manager->get_count() << " of " << (int)options.size() << std::endl;
        };

        m_service_manager->set_num_threads(1); // for indicating writing progress
        m_service_manager->start();

        while(m_service_manager->is_running()) {
            m_service_manager->run_task(process_indicator);
            usleep(0.3 * 1000 * 1000);  //intervals for indications
        }

        //cout << m_service_manager->is_running() << endl;

        m_service_manager->shutdown();

    } catch(runtime_error& e) {
        cerr << e.what() << endl;
    }


    return 0;
}
