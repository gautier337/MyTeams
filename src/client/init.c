/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** init
*/

#include "myteams.h"

client_t *create_client(char *ip, int port)
{
    client_t *client = malloc(sizeof(client_t));
    struct sockaddr_in adr = {0};

    if (!ip || port == -1)
        exit_error("Invalid arguments\n");
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = inet_addr(ip);
    if ((client->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        free(client);
        exit_error("socket()");
    }
    if (connect(client->sockfd, (struct sockaddr *)&adr, sizeof(adr)) < 0) {
        close_socket(client->sockfd);
        free(client);
        exit_error("connect()");
    }
    client->is_connected = true;
    client->user_status = 0;
    return client;
}
