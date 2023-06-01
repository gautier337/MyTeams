/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** users
*/

#include "myteams.h"

bool is_user_in_db(const char *user_name)
{
    char *file_content = NULL;
    bool client_exists = false;
    char *line = NULL;
    char *user_name_in_file = NULL;
    char *line_save_ptr = NULL;
    char *user_name_save_ptr = NULL;

    if (!user_name || !(file_content = read_file(USERS_LIST_PATH)))
        return false;
    line = strtok_r(file_content, "\n", &line_save_ptr);
    while (line != NULL && !client_exists) {
        user_name_save_ptr = NULL;
        user_name_in_file = strtok_r(line, ",", &user_name_save_ptr);
        if (user_name_in_file && my_strcmp(user_name_in_file, user_name) == 0)
            client_exists = true;
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
    free(file_content);
    return client_exists;
}

bool is_uuid_in_db(const char *user_uuid)
{
    char *file_content = NULL;
    char *line = NULL;
    char *token = NULL;
    char *saveptr_line = NULL;
    char *saveptr_token = NULL;

    if (!user_uuid || !(file_content = read_file(USERS_LIST_PATH)))
        return false;
    line = strtok_r(file_content, "\n", &saveptr_line);
    while (line != NULL) {
        token = strtok_r(line, ",", &saveptr_token);
        if ((token = strtok_r(NULL, ",", &saveptr_token)) &&
            strncmp(token, user_uuid, strlen(user_uuid)) == 0) {
            free(file_content);
            return true;
        }
        line = strtok_r(NULL, "\n", &saveptr_line);
    }
    free(file_content);
    return false;
}

void append_user_to_db(
    const char *user_name, const char *user_uuid, int status)
{
    char *file_content_users = NULL;
    char *status_as_str = my_put_nbr_in_str(status);

    if (!user_name || !user_uuid || !status_as_str)
        exit_error("append_user_to_db()");
    file_content_users = read_file(USERS_LIST_PATH);
    if (file_content_users)
        if (file_content_users[my_strlen(file_content_users) - 1] != '\n')
            append_file(USERS_LIST_PATH, "\n");
    append_file(USERS_LIST_PATH, user_name);
    append_file(USERS_LIST_PATH, ",");
    append_file(USERS_LIST_PATH, user_uuid);
    append_file(USERS_LIST_PATH, ",");
    append_file(USERS_LIST_PATH, status_as_str);
    append_file(USERS_LIST_PATH, "\n");
    free(status_as_str);
}

char *update_status(char *line, int status)
{
    char *status_as_str = my_put_nbr_in_str(status);
    char *line_without_status = NULL;
    char *line_with_new_status = NULL;

    if (!line || !status_as_str)
        return NULL;
    line_without_status = strndup(line, my_strlen(line) - 1);
    line_with_new_status = my_strcat(line_without_status, status_as_str);
    free(status_as_str);
    free(line_without_status);
    return line_with_new_status;
}

void update_user_status_in_db(const char *user_name, int status)
{
    char *file_content = NULL;
    char *line = NULL;
    char *new_line = NULL;

    if (!(file_content = read_file(USERS_LIST_PATH)))
        exit_error("update_user_status_in_db()");
    write_file(USERS_LIST_PATH, "");
    line = strtok(file_content, "\n");
    while (line != NULL) {
        if (!my_strncmp(line, user_name, my_strlen(user_name)))
            new_line = update_status(line, status);
        else
            new_line = strdup(line);
        append_file(USERS_LIST_PATH, new_line);
        append_file(USERS_LIST_PATH, "\n");
        free(new_line);
        line = strtok(NULL, "\n");
    }
    free(file_content);
}
