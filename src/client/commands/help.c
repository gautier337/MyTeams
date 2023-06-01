/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** help
*/

#include "myteams.h"

void help_client(client_t *client, const char *response)
{
    if (!client || !response)
        return;
    if (!strncmp(API_NO_CONTENT, response, 3)) {
        my_printf("No helper.\r\n");
        return;
    }
    my_printf("%s", response);
}
