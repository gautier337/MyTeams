/*
** EPITECH PROJECT, 2023
** subscribe
** File description:
** subscribed
*/

#include "myteams.h"

void send_to_user_with_state(client_t *client, int state, char *data)
{
    char *output = NULL;

    if (!client || !data)
        return;
    if (!(output = msprintf("%d,%s", state, data)))
        return;
    send_to_user(client, output);
    free(output);
}

void return_output_if_not_null(client_t *client, char *output, int state)
{
    if (!output)
        return send_to_user_with_state(client, state, API_NO_CONTENT);
    send_to_user(client, output);
    free(output);
}

void subscribed_command_teams(client_t *client)
{
    DIR *dir = NULL;
    char *output = NULL;
    char *team_infos = NULL;

    if (!(dir = opendir("data/teams")))
        return send_to_user_with_state(client, 0, API_NO_CONTENT);
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir)) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR ||
            !check_if_user_is_subscribe_to_the_team(entry->d_name,
            client->user_uuid))
            continue;
        if (!(team_infos = get_team_infos_from_uuid(entry->d_name)))
            continue;
        add_line_to_data(&output, team_infos, 0);
    }
    return return_output_if_not_null(client, output, 0);
}

void subscribed_command_users(client_t *client, const char *team_uuid)
{
    char *filename = NULL;
    char *file_content = NULL;
    char *user_uuid = NULL;
    char *user_infos = NULL;
    char *output = NULL;

    if (handle_subscribed_errors_users(client, team_uuid))
        return;
    filename = msprintf("data/teams/%s/users.csv", team_uuid);
    file_content = read_file(filename);
    free(filename);
    user_uuid = strtok(file_content, "\n");
    while (user_uuid) {
        if (!(user_infos = get_user_infos_from_uuid(user_uuid)))
            continue;
        add_line_to_data(&output, user_infos, 1);
        user_uuid = strtok(NULL, "\n");
    }
    return return_output_if_not_null(client, output, 1);
}

void subscribed_command(server_t *server, client_t *client,
        const char **params)
{
    int nb_args = 0;

    if (!server || !client || !params)
        return;
    if ((nb_args = my_arrlen((char **)params)) > 2)
        return send_to_user_with_state(client, 0, API_INVALID_SYNTAX);
    switch (nb_args) {
        case 1:
            return subscribed_command_teams(client);
        case 2:
            return subscribed_command_users(client, params[1]);
    }
}
