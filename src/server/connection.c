/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** connection.c
*/

#include "myteams.h"

int accept_connection(int sockfd)
{
    int fd = 0;
    struct sockaddr_in adr = {0};
    socklen_t adr_len = sizeof(adr);
    char *ip = NULL;
    int port = 0;

    if ((fd = accept(sockfd, (struct sockaddr *)&adr, &adr_len)) < 0)
        exit_error("accept()");
    if (!(ip = inet_ntoa(adr.sin_addr)))
        exit_error("inet_ntoa()");
    port = ntohs(adr.sin_port);
    printf("Client connected from %s:%d\n", ip, port);
    return fd;
}

context_t *init_client_context(void)
{
    context_t *context = malloc(sizeof(context_t));

    if (!context)
        exit_error("malloc()");
    context->type = NO_CONTEXT;
    context->team_uuid = NULL;
    context->channel_uuid = NULL;
    context->thread_uuid = NULL;
    return context;
}

void accept_new_connection(
    server_t *server, client_t *clients, int *nb_clients, int *max_fd)
{
    int client_sockfd = 0;

    if (!server)
        return;
    client_sockfd = accept_connection(server->sockfd);
    if (*nb_clients == MAX_CLIENTS) {
        close_socket(client_sockfd);
        exit_error("Too many clients connected");
    }
    clients[*nb_clients].sockfd = client_sockfd;
    clients[*nb_clients].is_connected = true;
    clients[*nb_clients].context = init_client_context();
    (*nb_clients) += 1;
    if (client_sockfd > *max_fd)
        *max_fd = client_sockfd;
}
