/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** login
*/

#include "myteams.h"

void login_client(client_t *client, const char *response)
{
    if (!client || !response)
        return;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax. Please use: /login \"username\"\r\n");
        return;
    }
    if (!strncmp(API_METHOD_NOT_ALLOWED, response, 3)) {
        my_printf("Already logged in\r\n");
        return;
    }
}
