#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>

namespace todo
{
class application
{
  private:
    std::string m_appname;
    std::string m_error;
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
      kList
    } m_action;

    bool fill_parameters(int argc, char *argv[]);
    bool status;

    void print_usage(std::string const & p_error = "");

  public:
		application(int argc, char *argv[]);
    int run();
};

}

#endif
