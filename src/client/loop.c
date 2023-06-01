/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** loop
*/

#include "myteams.h"
#include <signal.h>

void setup_fd_set(fd_set *read_fds, int sockfd)
{
    FD_ZERO(read_fds);
    FD_SET(sockfd, read_fds);
    FD_SET(STDIN_FILENO, read_fds);
}

void handle_stdin_input(client_t *client)
{
    char buf[READ_BUFFER_SIZE];

    if (fgets(buf, sizeof(buf), stdin) == NULL)
        exit(SUCCESS);
    if (client->buffer)
        free(client->buffer);
    client->buffer = strdup(buf);
    dprintf(client->sockfd, "%s", buf);
}

void handle_read_server(client_t *client)
{
    char buf[1024 * READ_BUFFER_SIZE];
    int num_bytes = 0;

    if (!client)
        exit_error("Client is NULL!");
    if ((num_bytes = recv(
        client->sockfd, buf, 1024 * READ_BUFFER_SIZE - 1, 0)) <= 0)
        exit_error("recv()");
    buf[num_bytes] = '\0';
    handle_server_response(client, buf);
    my_printf("\r\n> ");
}

void client_loop(client_t *client)
{
    fd_set read_fds;

    if (!client)
        exit_error("Client is NULL!");
    my_printf("> ");
    while (1) {
        setup_fd_set(&read_fds, client->sockfd);
        if (select(client->sockfd + 1, &read_fds, NULL, NULL, NULL) == -1)
            exit_error("select()");
        if (FD_ISSET(STDIN_FILENO, &read_fds))
            handle_stdin_input(client);
        if (FD_ISSET(client->sockfd, &read_fds))
            handle_read_server(client);
    }
    logout_client(client, "/logout");
}
