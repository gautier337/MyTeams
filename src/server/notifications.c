/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** notifications.c
*/

#include "myteams.h"

int process_line(client_t *clients, const char *line)
{
    char *notification = NULL;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected &&
            clients[i].user_uuid &&
            clients[i].is_logged_in &&
            !strncmp(clients[i].user_uuid, line,
            strlen(clients[i].user_uuid))) {
            notification = msprintf("%s %s", API_NOTIFIED, line);
            send_to_user(&clients[i], notification);
            free(notification);
            return 1;
        }
    }
    return 0;
}

char *build_temp_buffer(char *temp_buffer, const char *line)
{
    if (temp_buffer == NULL)
        return msprintf("%s", line);
    else {
        char *old_temp_buffer = temp_buffer;
        temp_buffer = msprintf("%s\n%s", old_temp_buffer, line);
        free(old_temp_buffer);
        return temp_buffer;
    }
}

void write_temp_buffer_to_file(char *temp_buffer)
{
    FILE *file = fopen("./data/messages.csv", "w");
    if (file != NULL) {
        if (temp_buffer != NULL) {
            fputs(temp_buffer, file);
            free(temp_buffer);
        }
        fclose(file);
    }
}

void handle_notifications(client_t *clients)
{
    char *line = NULL;
    char *file_buffer = NULL;
    char *temp_buffer = NULL;

    if (!(file_buffer = read_file("./data/messages.csv")))
        return;
    line = strtok(file_buffer, "\n");
    while (line != NULL) {
        if (!process_line(clients, line)) {
            temp_buffer = build_temp_buffer(temp_buffer, line);
        }
        line = strtok(NULL, "\n");
    }

    write_temp_buffer_to_file(temp_buffer);
    free(file_buffer);
}
