/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** subscribed_functions
*/

#include "myteams.h"

bool handle_subscribed_errors_users_not_found(
    client_t *client, const char *team_uuid)
{
    char *output = NULL;

    if (!client)
        return false;
    output = msprintf("%s,%s", API_NOT_FOUND, team_uuid);
    send_to_user_with_state(client, 1, output);
    free(output);
    return true;
}

bool handle_subscribed_errors_users(client_t *client, const char *team_uuid)
{
    char *dirname = NULL;
    char *filename = NULL;
    char *file_content = NULL;
    char *output = NULL;

    dirname = msprintf("data/teams/%s", team_uuid);
    if (!opendir(dirname)) {
        free(dirname);
        return handle_subscribed_errors_users_not_found(client, team_uuid);
    }
    filename = msprintf("data/teams/%s/users.csv", team_uuid);
    if (!(file_content = read_file(filename))) {
        output = msprintf("%s,%s", API_NO_CONTENT, team_uuid);
        send_to_user_with_state(client, 1, output);
        free(output);
        return true;
    }
    free(filename);
    free(file_content);
    return false;
}
