/*
** EPITECH PROJECT, 2023
** Load_user
** File description:
** load_user
*/

#include "myteams.h"

char **get_user_data_from_line(char *line)
{
    char **user_data = NULL;

    if (!line)
        exit_error("get_user_data_from_line()");
    if (!(user_data = malloc(sizeof(char *) * 4)))
        exit_error("user_data(): malloc");
    user_data[0] = strdup(strtok(line, ","));
    user_data[1] = strdup(strtok(NULL, ","));
    user_data[2] = strdup(strtok(NULL, ","));
    user_data[3] = NULL;
    if (my_arrlen(user_data) != 3)
        exit_error("get_user_data_from_line(): user_data");
    return user_data;
}

char *get_user_name_from_line(const char *line)
{
    char *temp_line = NULL;
    char *user_name = NULL;
    char *user_name_save_ptr = NULL;
    char *result_user_name = NULL;

    if (!(temp_line = strdup(line)))
        exit_error("get_user_name_from_line(): strdup");
    user_name = strtok_r(temp_line, ",", &user_name_save_ptr);
    if (user_name) {
        result_user_name = strdup(user_name);
        if (!result_user_name)
            exit_error("get_user_name_from_line(): strdup()");
        free(temp_line);
        return result_user_name;
    }
    free(temp_line);
    return NULL;
}

char **return_user_data(char *user_name, char *file_content, char *line)
{
    char **user_data = NULL;

    if (!user_name || !file_content || !line)
        exit_error("return_user_data()");
    user_data = get_user_data_from_line(line);
    free(user_name);
    free(file_content);
    return user_data;
}

char **load_user_from_db(const char *user_name)
{
    char *file_content = NULL;
    char *line = NULL;
    char *line_save_ptr = NULL;
    char *user_name_in_file = NULL;

    if (!user_name)
        exit_error("load_user_from_db()");
    if (!(file_content = read_file(USERS_LIST_PATH)))
        return NULL;
    line = strtok_r(file_content, "\n", &line_save_ptr);
    while (line != NULL) {
        user_name_in_file = get_user_name_from_line(line);
        if (user_name_in_file && my_strcmp(user_name_in_file, user_name) == 0)
            return return_user_data(user_name_in_file, file_content, line);
        free(user_name_in_file);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
    free(file_content);
    return NULL;
}
