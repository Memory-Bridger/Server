// Copyright (c) 2024 Memory-Bridger
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef ACCEPT_SOCKET_H
#define ACCEPT_SOCKET_H

#include <netinet/in.h>

typedef struct accept_socket {
    int listen_socket_sock_fd;

    int sock_fd;
    struct sockaddr_in sock_addr;
    socklen_t sock_addr_len;
    char ip_addr[INET_ADDRSTRLEN];
    unsigned short ip_port;
} accept_socket_t;

accept_socket_t *init_accept_socket(int listen_socket_sock_fd);
void terminate_accept_socket(accept_socket_t *accept_socket);

int accept_socket_accept(accept_socket_t *accept_socket);

#endif  // ACCEPT_SOCKET_H
