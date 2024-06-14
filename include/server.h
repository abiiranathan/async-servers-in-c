#ifndef SERVER_H
#define SERVER_H

#include "http.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <solidc/cstr.h>
#include <solidc/filepath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_EVENTS 1024

typedef struct TCPServer {
    int server_fd;
    struct sockaddr_in server_addr;
    int port;
    int epoll_fd;
} TCPServer;

// Takes in method and path and returns the matching handler.
typedef Route* (*ServeMux)(HttpMethod method, URL* url);

// Create a IPV4 TCP server and bind to port.
TCPServer* new_tcpserver(int port);

// Set socket file descriptor to non-blocking mode.
int set_nonblocking(int sockfd);

// Register a socket file descriptor with epoll.
// Specify the events to register.
void epoll_ctl_add(int epoll_fd, int sock_fd, struct epoll_event* event, uint32_t events);

// Start the event loop and run server on specified port.
void listen_and_serve(TCPServer* server, ServeMux mux, int num_threads);

// Start the event loop and run server on specified port.
// Serve TLS.
void listen_and_serve_tls(TCPServer* server, ServeMux mux, const char* cerffile, const char* keyfile);

#endif /* SERVER_H */