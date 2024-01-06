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

#include "accept_socket.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

accept_socket_t *init_accept_socket(int listen_socket_sock_fd) {
    accept_socket_t *accept_socket = malloc(sizeof(accept_socket_t));
    if (accept_socket == NULL) {
        perror("init_accept_socket: malloc");
        return NULL;
    }

    memset(accept_socket, 0, sizeof(accept_socket_t));

    accept_socket->listen_socket_sock_fd = listen_socket_sock_fd;

    return accept_socket;
}

void terminate_accept_socket(accept_socket_t *accept_socket) {
    close(accept_socket->sock_fd);

    free(accept_socket);
}

int accept_socket_accept(accept_socket_t *accept_socket) {
    accept_socket->sock_fd = accept(accept_socket->listen_socket_sock_fd,
        (struct sockaddr *)&accept_socket->sock_addr,
        &accept_socket->sock_addr_len);
    if (accept_socket->sock_fd == -1) {
        perror("accept_socket_accept: accept");
        return EXIT_FAILURE;
    }

    memset(accept_socket->ip_addr, 0, INET_ADDRSTRLEN);
    if (inet_ntop(AF_INET, &accept_socket->sock_addr.sin_addr,
        accept_socket->ip_addr, INET_ADDRSTRLEN) == NULL) {
        perror("accept_socket_accept: inet_ntop");
        return EXIT_FAILURE;
    }

    accept_socket->ip_port = ntohs(accept_socket->sock_addr.sin_port);

    return EXIT_SUCCESS;
}
