/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** client.c
*/

#include "myteams.h"

int handle_client(server_t *server, client_t *client)
{
    if (!server || !client)
        exit_error("handle_client()");
    client->buffer = read_from_fd(client->sockfd, READ_BUFFER_SIZE);
    command_manager(server, client);
    free(client->buffer);
    return SUCCESS;
}

void handle_clients(server_t *server, client_t *clients,
    int nb_clients, fd_set read_fds)
{
    int ret = 0;

    if (!server || !clients || !nb_clients)
        exit_error("handle_clients()");

    for (int i = 0; i < nb_clients; i += 1) {
        if (!FD_ISSET(clients[i].sockfd, &read_fds))
            continue;
        ret = handle_client(server, &clients[i]);
        if (ret == ERROR) {
            close_socket(clients[i].sockfd);
            clients[i].is_connected = false;
        }
    }
}

void disconnect_client(client_t *client)
{
    if (!client)
        return;
    if (client->user_status == 1) {
        update_user_status_in_db(client->user_name, 0);
        server_event_user_logged_out(client->user_uuid);
        append_log_event(0, client->user_uuid, client->user_name);
        if (client->user_uuid)
            free(client->user_uuid);
        if (client->user_name)
            free(client->user_name);
        client->user_status = 0;
        client->is_logged_in = false;
        client->is_temp_logged_in = false;
    }
    printf("Client %d disconnected\n", client->sockfd);
    close(client->sockfd);
    client->is_connected = false;
}

void reorganize_clients(client_t *clients, int *nb_clients)
{
    int j = 0;

    if (!clients || !nb_clients)
        return exit_error("reorganized_clients()");
    for (int i = 0; i < *nb_clients; i++) {
        if (!clients[i].is_connected)
            continue;
        if (i != j)
            clients[j] = clients[i];
        j += 1;
    }
    *nb_clients = j;
}

void remove_disconnected_clients(client_t *clients, int *nb_clients)
{
    char buffer[1024] = {0};
    int rv = 0;
    client_t *client = NULL;

    if (!clients || !nb_clients)
        return exit_error("remove_disconnected_clients()");
    for (int i = 0; i < *nb_clients; i += 1) {
        client = &clients[i];
        rv = recv(client->sockfd, buffer,
            sizeof(buffer), MSG_PEEK | MSG_DONTWAIT);
        if (rv == 0 || (rv < 0 && errno != EAGAIN && errno != EWOULDBLOCK))
            disconnect_client(client);
    }
    reorganize_clients(clients, nb_clients);
}
