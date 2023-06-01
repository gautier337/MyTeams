/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** main.c
*/

#include "myteams.h"

void print_client_usage(void)
{
    printf("USAGE: ./myteams_client ip port\n");
    printf("\tip is the server ip address on which ");
    printf("the server socket listens.\n");
    printf("\tport is the port number on on which ");
    printf("the server socket listens.\n");
    exit(SUCCESS);
}

int get_port(char *port)
{
    int port_nbr = 0;

    if (!port)
        return -1;
    port_nbr = atoi(port);
    if (port_nbr < 1024 || port_nbr > 65535)
        exit_error("Port must be between 1024 and 65535\n");
    return port_nbr;
}

void destroy_client(client_t *client)
{
    if (!client)
        return;
    if (client->buffer)
        free(client->buffer);
    free(client);
}

int client(char *ip, char *port)
{
    client_t *client = NULL;

    if (!ip || !port)
        return ERROR;
    client = create_client(ip, get_port(port));
    client_loop(client);
    close_socket(client->sockfd);
    destroy_client(client);
    return SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc != 3 || my_strcmp(argv[1], "-h") == 0)
        print_client_usage();
    return client(argv[1], argv[2]);
}
