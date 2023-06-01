/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** users
*/

#include "myteams.h"

void print_user(char *user_data, client_t *client)
{
    char *user[3] = {NULL};
    char *token = NULL;
    int idx = 0;

    if (!user_data || !client)
        exit_error("print_user()");
    token = strtok(user_data, ",");
    while (token != NULL && idx < 3) {
        user[idx] = token;
        token = strtok(NULL, ",");
        idx++;
    }
    if (idx != 3)
        exit_error("print_user(): bad user_data");
    client_print_users(user[1], user[0], atoi(user[2]));
}

void users_client(client_t *client, const char *response)
{
    char *user = NULL;
    char *next_line = NULL;

    if (!client || !response)
        return;
    user = strtok_r((char *)response, "\n", &next_line);
    while (user != NULL) {
        print_user(user, client);
        user = strtok_r(NULL, "\n", &next_line);
    }
}
