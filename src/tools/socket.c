/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** socket.c
*/

#include "myteams.h"

void close_socket(int sockfd)
{
    if (close(sockfd) < 0)
        exit_error("close()");
}
