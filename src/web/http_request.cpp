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


#include "http_request.h"
#include <string>

using namespace todo;

http_request::http_request(std::string const & p_request)
{
  bool l_value(false);
  bool l_key(true);

  std::string l_keyValue;
  std::string l_valueValue;
  std::string l_request;
  l_request = p_request.substr(0, p_request.find_first_of('\r'));
  std::string l_rest = p_request.substr(p_request.find_first_of('\n'));

  // Special header to store the HTTP_Request
  m_headers["HTTP_Request"] = l_request;

  // The most stupid parsing ever.
  for (const char & n : l_rest)
  {
    // Here we have finished parsing a key
    if (n == ':') {
      l_value = true;
      l_key = false;
      continue;
    }

    // Here we have finished parsing a value, hence we have everything
    else if (n == '\r' or n == '\n') {
      l_value = false;
      l_key = true;

      // We don't care about doing it twice, this is a map.
      if (not l_keyValue.empty())
        // the first character is empty, avoid it
        m_headers[l_keyValue] = l_valueValue.substr(1);

      l_keyValue.clear();
      l_valueValue.clear();
      continue;
    }

    if (l_key) l_keyValue += n;
    if (l_value) l_valueValue += n;
  }
}

http_request::const_iterator http_request::begin() const
{
  return m_headers.begin();
}

http_request::const_iterator http_request::end() const
{
  return m_headers.end();
}

http_request::iterator http_request::begin()
{
  return m_headers.begin();
}

http_request::iterator http_request::end()
{
  return m_headers.end();
}

void http_request::insert(header_t const & p_header)
{
  m_headers[p_header.first] = p_header.second;
}
