/*
** EPITECH PROJECT, 2023
** reply notifications
** File description:
** reply_notifications
*/

#include "myteams.h"

char *extract_team_uuid(const char *line)
{
    char *line_copy = NULL;
    char *team_uuid = NULL;

    if (!line)
        return NULL;
    line_copy = strdup(line);
    if (!line_copy)
        return NULL;
    team_uuid = strtok(line_copy, "¤");
    if (!team_uuid) {
        free(line_copy);
        return NULL;
    }
    team_uuid = strdup(team_uuid);
    free(line_copy);
    return team_uuid;
}

int process_line_reply(client_t *clients, const char *line)
{
    char *notification = NULL;
    char *team_uuid = NULL;

    if (!line || !clients)
        return 84;
    if (!(notification = msprintf("%s¤%s", API_REPLY_EVENT, line)))
        return 84;
    if (!(team_uuid = extract_team_uuid(line))) {
        free(notification);
        return 84;
    }
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (clients[i].is_connected && clients[i].user_uuid
            && clients[i].is_logged_in &&
            check_if_user_is_subscribe_to_the_team(team_uuid,
                clients[i].user_uuid))
            send_to_user(&clients[i], notification);
    free(team_uuid);
    free(notification);
    return 0;
}

void clear_file_reply(void)
{
    FILE *file = fopen("./data/reply_events.csv", "w");

    if (!file)
        exit_error("Error: fopen()");
    fclose(file);
}

void handle_notifications_reply(client_t *clients)
{
    char *line = NULL;
    char *file_buffer = NULL;
    char *temp_buffer = NULL;

    if (!(file_buffer = read_file("./data/reply_events.csv")))
        return;
    line = strtok(file_buffer, "\n");
    while (line != NULL) {
        if (process_line_reply(clients, line) == 84)
            exit_error("Error: process_line_reply()");
        line = strtok(NULL, "\n");
    }
    clear_file_reply();
    if (temp_buffer)
        free(temp_buffer);
    free(file_buffer);
}
