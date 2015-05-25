#include <iostream>
#include "service_manager.h"

service_manager::service_manager(std::shared_ptr<settings> const &settings) :
        m_settings(settings),
        num_threads(1),
        running(false),
        fields_filled(0) {

}

service_manager::~service_manager() {

}

void service_manager::run_service(const std::shared_ptr<service>& service) {
    mutex.lock();
    services.push_back(service);
    mutex.unlock();

    if (running) {
        service->run();
    }
}

void service_manager::start() {
    if (!running) {
        running = true;

        mutex.lock();
        for(int i = 0; i < (int)services.size(); i++) {
            services[i]->run();
        }
        mutex.unlock();

        for(int i = 0; i < this->num_threads; i++) {
            threads.push_back(std::thread([this]()-> void{
                while(running) {
                    task_t tsk = tasks.pop();
                    //std::cout << "runs - " << std::this_thread::get_id() << std::endl;
                    tsk();
                }
            }));
        }
    } else {
        throw new std::runtime_error("instance of service_manager already started");
    }
}

void service_manager::shutdown() {
    if (running) {
        running = false;

        for(int i = 0; i < (int)services.size(); i++) {
            services[i]->shutdown();
        }

        for(int i = 0; i < (int)threads.size(); i++) {
            if (threads[i].joinable()) {
                threads[i].join();
            }

        }
    } else {
        //throw new std::runtime_error("instance of service_manager is not running");
    }
}

void service_manager::run_task(const task_t& task) {
    tasks.push(task);
}

void service_manager::set_num_threads(size_t count) {
    if (!running) {
        this->num_threads = count;
    } else {
        throw new std::runtime_error("try to set_num_threads when running");
    }

}

/* Methods for manupulations with status */

bool service_manager::is_running() {
    return running;
}

void service_manager::set_running(bool value) {
    running = value;
}

/* Methods for quick checking progress */

void service_manager::inc_count() {
    fields_filled++;
}

int service_manager::get_count() {
    return fields_filled;
}
