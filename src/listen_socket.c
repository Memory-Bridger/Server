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

#include "listen_socket.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

listen_socket_t *init_listen_socket(char ip_addr[INET_ADDRSTRLEN],
    unsigned short ip_port) {
    listen_socket_t *listen_socket = malloc(sizeof(listen_socket_t));
    if (listen_socket == NULL) {
        perror("init_listen_socket: malloc");
        return NULL;
    }

    memset(listen_socket, 0, sizeof(listen_socket_t));

    strcpy(listen_socket->ip_addr, ip_addr);
    listen_socket->ip_port = ip_port;

    listen_socket->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket->sock_fd == -1) {
        perror("init_listen_socket: socket");
        return NULL;
    }

    return listen_socket;
}

void terminate_listen_socket(listen_socket_t *listen_socket) {
    close(listen_socket->sock_fd);

    free(listen_socket);
}

int listen_socket_bind(listen_socket_t *listen_socket) {
    listen_socket->sock_addr.sin_family = AF_INET;
    listen_socket->sock_addr.sin_addr.s_addr = inet_addr(listen_socket->ip_addr);
    listen_socket->sock_addr.sin_port = htons(listen_socket->ip_port);

    if (bind(listen_socket->sock_fd,
        (struct sockaddr *)&listen_socket->sock_addr,
        sizeof(listen_socket->sock_addr)) == -1) {
        perror("listen_socket_bind: bind");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int listen_socket_listen(listen_socket_t *listen_socket) {
    if (listen(listen_socket->sock_fd, SOMAXCONN) == -1) {
        perror("listen_socket_listen: listen");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int listen_socket_get_sock_fd(listen_socket_t *listen_socket) {
    return listen_socket->sock_fd;
}
