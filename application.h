#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <map>

namespace todo
{
class config;

class application
{
  private:
    std::string m_appname;
    std::string m_error;
    std::map<std::string, std::string> m_colors;
    config * m_config;
    class parameters
    {
      public:
        std::string   m_action;
        std::string   m_todorc;
        std::string   m_tododb;

        std::string   m_body;
        std::string   m_title;
        uint32_t      m_priority;

        uint32_t      m_note_id;

        bool          m_filling_body;
        bool          m_verbose;
    } m_parameters;

    enum {
      kInsert,
      kDelete,
      kModify,
      kList,
      kSearch
    } m_action;

    bool fill_parameters(int argc, char *argv[]);
    bool status;

    void print_usage();

    std::string print_color(std::string const & l_color,
                           std::string const & l_string,
                           bool bright = true,
                           bool underline = false);
    std::string print_color(std::string const & l_color,
                           int l_number,
                           bool bright = true,
                           bool underline = false);

    void pretty_print_element(todo::element const & p_element);

  public:
		application(int argc, char *argv[]);
    virtual ~application();
    int run();
};

}

#endif
