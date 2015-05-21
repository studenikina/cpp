#ifndef CPP_SERVICEMANAGER_H
#define CPP_SERVICEMANAGER_H

#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "../SettingsLib/settings.h"
#include "queue.h"


class service_manager;

class service {
public:
    virtual void setup(std::shared_ptr<settings> const & sets,
                       std::shared_ptr<service_manager> const & manager) = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;
};

class service_manager {
public:
    typedef std::shared_ptr<service_manager> service_manager_ptr;
    typedef std::function<void()> task_t;

    service_manager(std::shared_ptr<settings> const & settings);
    ~service_manager();

    void run_service(std::shared_ptr<service> const &);
    void start();
    void shutdown();

    void run_task(const task_t& task);
    void set_num_threads(size_t count);

    /* helpers */
    bool is_running();
    void set_running(bool value);
    void inc_count();
    int get_count();

    //Bonus
    void save_config();
    template<typename T>
    void register_service(std::string const & name);

    void add_startup_service(std::string const & name);
    void remove_startup_service(std::string const & name);
private:

    /* synchronization */
    std::mutex mutex;

    /* private members */
    std::shared_ptr<settings> m_settings;
    size_t num_threads;
    std::vector< std::shared_ptr<service> > services;
    bool running;

    std::vector<std::thread> threads;
    queue<task_t> tasks;

    int fields_filled; //count of fields already writed by services (for indicating)
};

#endif //CPP_SERVICEMANAGER_H
