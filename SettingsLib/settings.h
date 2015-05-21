#ifndef CPP_SETTINGS_H
#define CPP_SETTINGS_H


#include <vector>
#include <cstdlib>
#include <functional>
#include <memory>

class settings {
public:
    class param {
    public:
        typedef std::unique_ptr<param> param_ptr;
        friend class settings;

        operator std::string() const;
        operator int() const;
        operator bool() const;
        operator double() const;

        param & operator=(std::string const &);
        param & operator=(int);
        param & operator=(bool);
        param & operator=(double);

        param & operator+=(std::string const &);
        param & operator+=(int);
        param & operator+=(double);

        param & operator-=(int);
        param & operator-=(double);

        param & operator*=(int);
        param & operator*=(double);

        param & operator/=(int);
        param & operator/=(double);

        param & operator|=(bool);
        param & operator&=(bool);
        bool is_empty() const;
    private:
        param(std::string const&name, std::string const& value);
        param(param const& other);
        param(param_ptr const& other);

        std::string name, value;
    };

    // Main functions
    /**
     * Construct settings store
     * and load data from file (if exists)
     * \param filename Path to file with settings
     */
    settings(std::string const & filename);
    settings(const char* filename);
    /**
     * Get setting value
     * \param name Setting unique identifier
     * \param def Default setting value
     * \return Stored value for given name or default value
     */
    std::string const & get(std::string const & name, std::string const & def = "") const;
    /**
     * Set or replace setting value and save changes to file
     * \param name Setting unique identifier
     * \param value New setting value
     */
    void set(std::string const & name, std::string const & value);
    /**
     * Reset all settings
     */
    void reset();
    /**
     * Reload all settings from file
     */
    void reload();

    // Advanced funсtions

    /**
      * Get constant setting wrapper
      * \param name Setting unique identifier
      */
    const param operator[](std::string const & name) const;
    /**
      * Get constant setting wrapper
      * \param name Setting unique identifier
      */
    param operator[](std::string const & name);

private:
    std::vector<param::param_ptr> parse_file(std::string const& filename);
    param & find_by_name(std::string const& name) const;

    std::vector <param::param_ptr> params;
    std::string filename;
};

#endif //CPP_SETTINGS_H
