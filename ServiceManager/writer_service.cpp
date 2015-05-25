
#include <thread>
#include <iostream>
#include "writer_service.h"

writer_service::writer_service(int current_thread, int options_count, const std::string& name) :
        curent_thread(current_thread),
        options_count(options_count),
        name(name),
        running(false) {

}

writer_service::~writer_service() {

}


void writer_service::setup(std::shared_ptr<settings>const& sets, std::shared_ptr<service_manager> const& manager) {
    m_settings = sets;
    m_service_manager = manager;
}

void writer_service::run() {
    //std::cout << "service - " << name << " started\n";
    if (this->m_settings == nullptr) {
        throw new std::runtime_error("pointer to settings instance didn't define");
    } else if (this->m_service_manager == nullptr) {
        throw new std::runtime_error("pointer to service_manager instance didn't define");
    }
    if (!running) {
        running = true;
        runner = std::thread([this]()->void{
            std::string opt, prefix = "thread"+std::to_string(curent_thread)+"_option";
            for(int i = 0; running && i < options_count; i++) {
                opt = prefix+std::to_string(i + 1);
                mutex.lock();
                m_service_manager->inc_count();
                m_settings->set(opt, this->name);
                mutex.unlock();
            }
        });
        //runner.join();
    } else {
        throw new std::runtime_error("service["+this->name+"]: is already running");
    }
}

void writer_service::shutdown() {
    running = false;
    runner.join();
}

bool writer_service::is_running() {
    return running;
}