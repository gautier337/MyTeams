/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** main.c
*/

#include "myteams.h"

int print_server_usage(void)
{
    printf("USAGE: ./myteams_server port\n");
    printf("\tport is the port number on on which ");
    printf("the server socket listens.\n");
    return SUCCESS;
}

int get_server_port(char **args)
{
    int server_port = 0;

    if (!args)
        return -1;
    server_port = atoi(args[1]);
    if (server_port < 1024 || server_port > 65535) {
        my_puterror("Port must be between 1024 and 65535\n");
        return -1;
    }
    return server_port;
}

int main(int argc, char **argv)
{
    int server_port = 0;

    if (argc != 2 || my_strcmp(argv[1], "-h") == 0)
        return print_server_usage();
    if ((server_port = get_server_port(argv)) == -1)
        return ERROR;
    return myteams_server(server_port);
}
