/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** loop.c
*/

#include "myteams.h"

void connection_loop(server_t *server)
{
    int max_fd = server->sockfd;
    fd_set read_fds;
    client_t clients[MAX_CLIENTS] = {0};
    int nb_clients = 0;

    while (1) {
        init_fd_set(server->sockfd, clients, nb_clients, &read_fds);
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0)
            exit_error("select()");
        if (FD_ISSET(server->sockfd, &read_fds))
            accept_new_connection(server, clients, &nb_clients, &max_fd);
        handle_clients(server, clients, nb_clients, read_fds);
        handle_notifications(clients);
        handle_notifications_log(clients);
        handle_notifications_reply(clients);
        remove_disconnected_clients(clients, &nb_clients);
    }
}
