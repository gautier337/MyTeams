/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace) [WSL: Ubuntu]
** File description:
** events
*/

#include "myteams.h"

void append_log_event(int status, char *user_uuid, char *user_name)
{
    char *user_data = NULL;

    if (!user_uuid || !user_name)
        exit_error("append_log_event()");
    user_data = msprintf("%d,%s,%s\n", status, user_uuid, user_name);
    append_file("data/log_events.csv", user_data);
    free(user_data);
}
