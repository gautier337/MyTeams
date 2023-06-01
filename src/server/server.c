/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** myteams_server.c
*/

#include "myteams.h"

int myteams_server(int server_port)
{
    server_t *server = NULL;

    if (!(server = create_server(server_port)))
        return ERROR;
    load_users_from_db();
    connection_loop(server);
    close_socket(server->sockfd);
    return SUCCESS;
}
