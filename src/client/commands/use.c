/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** use
*/

#include "myteams.h"

void use_client(client_t *client, const char *response)
{
    if (!client || !response)
        return;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax. Please use: ");
        my_printf("/use ?<team_uuid> ?<channel_uuid> ?<thread_uuid>\r\n");
        return;
    }
    if (!strncmp(API_SUCCESS, response, 3)) {
        my_printf("Context changed.\r\n");
        return;
    }
}
