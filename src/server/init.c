/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** init.c
*/

#include "myteams.h"

int init_socket(int port)
{
    int sockfd = 0;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY
    };

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        exit_error("soket()");
    }
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close_socket(sockfd);
        exit_error("bind()");
    }
    printf("Server listening on port %d\n", port);
    return sockfd;
}

void init_queue(int sockfd)
{
    if (listen(sockfd, BACKLOG_SIZE) < 0)
        exit_error("listen()");
}

server_t *create_server(int port)
{
    int sockfd = -1;
    server_t *server = NULL;
    DIR *dir = NULL;

    sockfd = init_socket(port);
    init_queue(sockfd);
    if (!(server = malloc(sizeof(server_t)))) {
        close_socket(sockfd);
        exit_error("malloc()");
    }
    server->sockfd = sockfd;
    server->port = port;
    if (!(dir = opendir("data")))
        mkdir("data", 0777);
    else
        closedir(dir);
    return server;
}

void init_fd_set(
    int sockfd, client_t *clients, int nb_clients, fd_set *read_fds)
{
    FD_ZERO(read_fds);
    FD_SET(sockfd, read_fds);
    for (int i = 0; i < nb_clients; i += 1)
        FD_SET(clients[i].sockfd, read_fds);
}
