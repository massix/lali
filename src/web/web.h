//
//           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                   Version 2, December 2004
//
// Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
//
// Software :
// Copyright (C) 2014 Massimo Gengarelli <massimo.gengarelli@gmail.com>
//
// Everyone is permitted to copy and distribute verbatim or modified
// copies of this license document, and changing it is allowed as long
// as the name is changed.
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.
//


#ifndef _WEB_H_
#define _WEB_H_

#include <string>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "element.h"
#include "collection.h"
#include "http_request.h"
#include <vector>
#include <map>
#include <functional>

#ifndef __TESTABLE__
#define __TESTABLE__
#endif

namespace todo
{
  class web
  {
    typedef std::function<std::string(std::string const &, url::cgi_t const &, http_request &)> servlet_t;
    typedef std::map<std::string, servlet_t> servlets_t;
  public:
    web(uint32_t p_port);
    void run();
    void stop();

    typedef servlets_t::const_iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
    void insert(std::string const & p_key, servlet_t p_collection);

  private:
    uint32_t   m_port;
    servlets_t m_servlets;
    int        m_socket;
    bool       m_running;
  };
}

#endif
