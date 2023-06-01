/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** logout
*/

#include "myteams.h"

void logout_client(client_t *client, const char *response)
{
    if (!client || !response)
        return;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax. Please use: /logout\r\n");
        return;
    }
    client->is_logged_in = false;
    client->user_name = NULL;
    client->user_uuid = NULL;
}
