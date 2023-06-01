/*
** EPITECH PROJECT, 2023
** send
** File description:
** send
*/

#include "myteams.h"

void send_client(client_t *client, const char *response)
{
    if (!client || !response)
        return;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax.\n");
        my_printf("Please use: /send \"user_uuid\" \"message_body\"\r\n");
        return;
    }
    if (!strncmp(API_NO_CONTENT, response, 3)) {
        my_printf("User not found.\r\n");
        return;
    }
    if (!strncmp(API_SUCCESS, response, 3))
        return;
}
