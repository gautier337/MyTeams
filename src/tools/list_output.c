/*
** EPITECH PROJECT, 2023
** MyTeams [WSL: Ubuntu]
** File description:
** list_output
*/

#include "tools.h"

void add_line_to_data(
    char **data, char *line, enum context_type default_context)
{
    char *tmp_data = NULL;

    if (!data || !line)
        return;
    if (!(*data)) {
        *data = msprintf("%d,%s", default_context, line);
        free(line);
        return;
    }
    tmp_data = msprintf("%s%s", *data, line);
    free(*data);
    free(line);
    *data = tmp_data;
}

char *create_line_from_thread_file(client_t *client, const char *thread_uuid,
    char *file_content)
{
    char *thread_title = NULL;
    char *thread_body = NULL;
    char *thread_timestamp = NULL;

    if (!client || !client->context || !file_content)
        return NULL;
    thread_title = strtok(file_content, ",");
    thread_body = strtok(NULL, ",");
    thread_timestamp = strtok(NULL, "\n");
    return msprintf("%s,%s,%s,%s,%s\n", thread_uuid, client->user_uuid,
        thread_timestamp, thread_title, thread_body);
}

char *get_data_from_folder_file(char *dir, char *file)
{
    char *filename = NULL;
    char *data = NULL;

    if (!dir || !file)
        return NULL;
    filename = msprintf("%s/%s", dir, file);
    if (!(data = read_file(filename)))
        return NULL;
    free(filename);
    return data;
}
