/*
** EPITECH PROJECT, 2023
** load_users
** File description:
** load_users
*/

#include "myteams.h"

char **load_users_from_db(void)
{
    char *file_content = NULL;
    char *line = NULL;
    char *line_save_ptr = NULL;
    char *element_save_ptr = NULL;
    char *user_name = NULL;
    char *user_uuid = NULL;

    if (!(file_content = read_file(USERS_LIST_PATH)))
        return NULL;
    line = strtok_r(file_content, "\n", &line_save_ptr);
    while (line != NULL) {
        user_name = strtok_r(line, ",", &element_save_ptr);
        user_uuid = strtok_r(NULL, ",", &element_save_ptr);
        if (user_name && user_uuid)
            server_event_user_loaded(user_uuid, user_name);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
    free(file_content);
    return NULL;
}
