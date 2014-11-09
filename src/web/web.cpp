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
#include "collection.h"
#include <sys/socket.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <iostream>
#include <unistd.h>


using namespace todo;

web::web(uint32_t p_port) :
  m_port(p_port), m_socket(0), m_running(false)
{
  // Init the socket, for now we don't care whether the socket is valid or not
  m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void web::run()
{
  fprintf(stdout, "in run\n");
  if (m_socket)
  {
    struct sockaddr_in l_serverAddress;
    struct sockaddr_in l_clientAddress;
    char               l_buffer[4096];

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

    // Set the timeout
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Listen
    if (listen(m_socket, 1) == -1)
    {
      perror("listen(): ");
      return;
    }

    m_running = true;
    while (m_running) {
      int l_clientLength = sizeof(l_clientAddress);
      int l_accepted = accept(m_socket,
                              (struct sockaddr *) &l_clientAddress,
                              (socklen_t *) &l_clientLength);

      if (recv(l_accepted, l_buffer, 4096, 0) == -1)
      {
        perror("recv(): ");
        return;
      }

      // If we are here, we have a request to handle
      fprintf(stdout, "Request: '%s'\n", l_buffer);
      std::string l_response("HTTP/1.1 200 Okay\r\n"
                             "Server: lali-web\r\n"
                             "Content-Type: text/html\r\n\r\n");
      l_response += "<html><head><title>Lali web service</title></head>"
                    "<body>Welcome!</body></html>";

      ssize_t l_length = send(l_accepted,
                              l_response.c_str(),
                              l_response.size(),
                              0);
      if (l_length == -1) {
        perror("send(): ");
        return;
      }

      fprintf(stdout, "Response: '%s'\n", l_response.c_str());
      fprintf(stdout, "Size: %ld\n", l_length);
      close(l_accepted);
    }

    close(m_socket);
  }
}

