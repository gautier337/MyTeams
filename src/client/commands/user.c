/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** user
*/

#include "myteams.h"

void user_client(client_t *client, const char *response)
{
    char *user_name = NULL;
    char *user_uuid = NULL;
    char *user_status = NULL;

    if (!client || !response)
        return;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax. Please use: /user \"uuid\"\r\n");
        return;
    }
    if (!strncmp(API_NO_CONTENT, response, 3)) {
        my_printf("User not found.\r\n");
        return;
    }
    user_name = strtok((char *)response, ",");
    user_uuid = strtok(NULL, ",");
    user_status = strtok(NULL, ",");
    client_print_user(user_uuid, user_name, atoi(user_status));
}
