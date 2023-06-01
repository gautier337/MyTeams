/*
** EPITECH PROJECT, 2023
** user cmd
** File description:
** user
*/

#include "myteams.h"

char *find_user_line(char *file_content, const char *user_uuid)
{
    char *line = NULL;
    char *uuid = NULL;
    char *line_save_ptr = NULL;
    char *user_save_ptr = NULL;
    char *current_line = NULL;

    line = strtok_r(file_content, "\n", &line_save_ptr);
    while (line) {
        current_line = (char *)realloc(current_line, strlen(line) + 1);
        strcpy(current_line, line);
        strtok_r(line, ",", &user_save_ptr);
        uuid = strtok_r(NULL, ",", &user_save_ptr);
        if (uuid && my_strcmp(uuid, user_uuid) == 0)
            break;
        line = strtok_r(NULL, "\n", &line_save_ptr);
        clear_pointer((void**)&current_line);
    }
    return current_line;
}

void find_user(client_t *client, const char *user_uuid)
{
    char *file_content = NULL;
    char *current_line = NULL;

    if (!user_uuid || !(file_content = read_file(USERS_LIST_PATH)))
        exit_error("find_user()");
    current_line = find_user_line(file_content, user_uuid);
    if (current_line && strlen(current_line) > 0) {
        send_to_user(client, current_line);
        free(current_line);
    } else
        send_to_user(client, API_NO_CONTENT);
    free(file_content);
}

void user_command(server_t *server, client_t *client, const char **params)
{
    if (!server || !client || !params)
        exit_error("user_command()");
    if (!params[1])
        return send_to_user(client, API_INVALID_SYNTAX);
    find_user(client, params[1]);
}
