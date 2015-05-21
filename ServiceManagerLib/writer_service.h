/**
 * Class for parallel filling fields in settings (wrapped over single text file).
 * Implements interface service.
 *
 * In particular case filling is in 4 threads (in writer_service's). And tasks used for check current progress.
 * Initially every option in file: threadXXX_optionYYY = "", but after service_manager finished threadXXX_optionYYY = "threadXXX"
 * i.e. every thread fills only fields contains string "thread[current_thread_id]" as prefix;
 */

#ifndef CPP_HASHER_SERVICE_H
#define CPP_HASHER_SERVICE_H

#include "service_manager.h"
#include "../SettingsLib/settings.h"

class writer_service : public service {
public:
    writer_service(int current_thread, int options_count, const std::string& name);
    ~writer_service();
    void setup(std::shared_ptr<settings>const& sets, std::shared_ptr<service_manager> const& manager);
    void run();
    void shutdown();
    bool is_running();

private:

    /* synchronization */
    std::mutex mutex;

    /* private members */
    std::shared_ptr<settings> m_settings;
    std::shared_ptr<service_manager> m_service_manager;

    int curent_thread;
    int options_count;
    std::string name;
    bool running;

    std::thread runner;
};


#endif //CPP_HASHER_SERVICE_H
