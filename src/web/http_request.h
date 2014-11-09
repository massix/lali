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


#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include <string>
#include <map>

#ifndef __TESTABLE__
#define __TESTABLE__
#endif

namespace todo
{
  class http_request
  {
  public:
    typedef std::map<std::string, std::string>  headers_t;
    typedef std::pair<std::string, std::string> header_t;
    typedef headers_t::const_iterator const_iterator;
    typedef headers_t::iterator       iterator;
    typedef headers_t::value_type     value_type;

  public:
    http_request(std::string const & p_request);

  public:
    http_request::const_iterator begin() const;
    http_request::const_iterator end() const;
    http_request::iterator       begin();
    http_request::iterator       end();
    void insert(header_t const & p_header);

  private:
    headers_t m_headers;
  };
}

#endif
