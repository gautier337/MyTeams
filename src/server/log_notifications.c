/*
** EPITECH PROJECT, 2023
** log notifications
** File description:
** log_notifications
*/

#include "myteams.h"

int process_line_log(client_t *clients, const char *line)
{
    char *notification = NULL;

    if (!line || !clients)
        return 84;
    notification = msprintf("%s,%s", API_LOG_EVENT, line);
    if (!notification)
        return 84;
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (clients[i].is_temp_logged_in || (clients[i].is_connected &&
            clients[i].user_uuid && clients[i].is_logged_in)) {
            clients[i].is_temp_logged_in = false;
            send_to_user(&clients[i], notification);
        }
    free(notification);
    return 0;
}

void clear_file_log(void)
{
    FILE *file = fopen("./data/log_events.csv", "w");

    if (!file)
        exit_error("Error: fopen()");
    fclose(file);
}

void handle_notifications_log(client_t *clients)
{
    char *line = NULL;
    char *file_buffer = NULL;
    char *temp_buffer = NULL;

    if (!(file_buffer = read_file("./data/log_events.csv")))
        return;
    line = strtok(file_buffer, "\n");
    while (line != NULL) {
        if (process_line_log(clients, line) == 84)
            exit_error("Error: process_line_log()");
        line = strtok(NULL, "\n");
    }
    clear_file_log();
    if (temp_buffer)
        free(temp_buffer);
    free(file_buffer);
}
