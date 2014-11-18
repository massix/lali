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


#include "web.h"
#include "http_request.h"
#include <core/collection.h>
#include <flate/flate.h>
#include <core/config.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread>
#include <strings.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace todo;

web::web(config * p_config) :
  m_port(p_config->getServerPort()), m_socket(0), m_running(false), m_config(p_config)
{
  // Init the socket, for now we don't care whether the socket is valid or not
  m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  m_templates = (*p_config)[TEMPLATES_DIRECTORY];
  m_resources = (*p_config)[RESOURCES_DIRECTORY];

  // Register a dump configuration servlet
  m_servlets["/debug/"] = [&](std::string const & /*p_page*/,
                              url::cgi_t const & /*p_cgi*/,
                              http_request & p_request)->std::string {
    fprintf(stderr, "Debug interface activated\n");
    p_request.m_code = http_request::kOkay;
    p_request["Content-Type"] = "text/html";

    Flate * l_flate = NULL;
    flateSetFile(&l_flate, std::string(m_templates + "debug_template.html").c_str());

    for (config::value_type const & c_key : (*m_config)) {
      flateSetVar(l_flate, "key", c_key.first.c_str());
      flateSetVar(l_flate, "value", c_key.second.c_str());
      flateDumpTableLine(l_flate, "config");
    }

    return flatePage(l_flate);
  };

  // Register a debug servlet
  m_servlets["/servlet/test/"] = [](std::string const & p_page,
                                    url::cgi_t const & p_cgi,
                                    http_request & p_request)->std::string {
    p_request.m_code = http_request::kOkay;
    if (not (p_request["Cookie"] == "TestCookie=1"))
      p_request["Set-Cookie"] = "TestCookie=1; Max-Age=3600; Version=1";

    std::string l_resp("<html><head><title>Test servlet</title></head><body>");
    l_resp += "<h1>" + p_page + "</h1>";
    l_resp += "<div class=\"cgi\"><ul>";

    for (url::cgi_t::value_type const & c : p_cgi) {
      l_resp += "<li><b>" + c.first + "</b> = ";
      l_resp += "<i>" + c.second + "</i></li>";
    }

    l_resp += "</ul></div></body></html>";

    return l_resp;
  };

  // Resources
  m_servlets["/resources/"] = [&](std::string const & p_page,
                                  url::cgi_t const & /*p_cgi*/,
                                  http_request & p_request)->std::string {
    struct stat l_stat;
    std::string l_resource = m_resources + p_page;
    fprintf(stderr, "Looking for file %s\n", l_resource.c_str());
    if (stat(l_resource.c_str(), &l_stat) == -1) {
      p_request.m_code = http_request::kNotFound;
      return "";
    }
    else {
      std::ifstream l_file(l_resource.c_str(), std::ifstream::in);
      std::string str;

      l_file.seekg(0, std::ios::end);
      str.reserve(l_file.tellg());
      l_file.seekg(0, std::ios::beg);

      str.assign((std::istreambuf_iterator<char>(l_file)),
                 std::istreambuf_iterator<char>());

      // TODO: Set content-type according to the extension of the file
      p_request["Content-Type"] = "text/css";
      return str;
    }
  };
}

void web::stop()
{
  m_running = false;
}

void web::run()
{
  if (m_socket)
  {
    struct sockaddr_in l_serverAddress;
    struct sockaddr_in l_clientAddress;

    bzero(&l_serverAddress, sizeof(l_serverAddress));
    bzero(&l_clientAddress, sizeof(l_clientAddress));

    l_serverAddress.sin_family = AF_INET;
    l_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    l_serverAddress.sin_port = htons(m_port);

    // Set a timeout
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 1000;

    // Bind the socket
    if (bind(m_socket, (struct sockaddr *) &l_serverAddress, sizeof(l_serverAddress)) == -1)
    {
      perror("bind(): ");
      return;
    }

    // Reusable socket
    int yes = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      perror("setsockopt()");
      return;
    }

#ifdef SO_REUSEPORT
    setsockopt(m_socket, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int));
#endif

    // Listen
    if (listen(m_socket, 3) == -1)
    {
      perror("listen(): ");
      return;
    }

    m_running = true;
    while (m_running) {
      fd_set l_set;

      FD_ZERO(&l_set);
      FD_SET(m_socket, &l_set);
      select(m_socket + 1, &l_set, nullptr, nullptr, &tv);

      if (FD_ISSET(m_socket, &l_set) and m_running) {
        std::thread l_thread([&] {
          std::string l_request;
          int l_clientLength = sizeof(l_clientAddress);
          l_request.resize(4096);

          int l_accepted = accept(m_socket,
                                  (struct sockaddr *) &l_clientAddress,
                                  (socklen_t *) &l_clientLength);

          int32_t l_length = recv(l_accepted, (void *) l_request.data(), l_request.size(), 0);
          l_request.resize(l_length);

          // If we are here, we have a request to handle
          http_request l_headers(l_request);
          for (http_request::value_type const & l_value : l_headers)
            fprintf(stdout, "'%s' = '%s'\n", l_value.first.c_str(), l_value.second.c_str());

          fprintf(stdout, "path '%s'\n", l_headers.get_url()->get_full_path().c_str());
          fprintf(stdout, "page '%s'\n", l_headers.get_url()->get_page().c_str());

          // Call the servlet if we have it
          std::string l_html_response;
          http_request l_responseHeaders;
          l_responseHeaders["Content-Type"] = "text/html";
          l_responseHeaders["Connection"] = "close";

          if (m_servlets.find(l_headers.get_url()->get_full_path()) != m_servlets.end())
          {
            l_html_response = m_servlets[l_headers.get_url()->get_full_path()](l_headers.get_url()->get_page(),
                                                                               l_headers.get_url()->get_cgi(),
                                                                               l_responseHeaders);
          }
          else
          {
            l_responseHeaders.m_code = http_request::kNotFound;
            Flate * l_flate = NULL;

            flateSetFile(&l_flate, std::string(m_templates + "404_template.html").c_str());
            flateSetVar(l_flate, "servlet",
                        l_headers.get_url()->get_full_path().c_str());
            flateSetVar(l_flate, "page",
                        l_headers.get_url()->get_page().c_str());

            char * l_buffer = flatePage(l_flate);
            l_html_response = l_buffer;
          }


          l_responseHeaders["Server"] = "lali-web/" + std::string(PACKAGE_VERSION);
          l_responseHeaders["Content-Length"] = std::to_string(l_html_response.size());

          std::string l_response = l_responseHeaders.to_string();
          l_response += l_html_response;

          l_length = send(l_accepted,
                          l_response.c_str(),
                          l_response.size(),
                          0);

          close(l_accepted);
        });

        // Fork it in background
        l_thread.detach();
      }
    }

    fprintf(stdout, "[%p] closing\n", this);
    close(m_socket);
  }
}
