/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** logout.c
*/

#include "myteams.h"

void logout_command(server_t *server, client_t *client,
    const char **params)
{
    if (!server || !client || !params)
        exit_error("logout_command()");
    if (my_arrlen((char **)params) != 1)
        return send_to_user(client, API_INVALID_SYNTAX);
    update_user_status_in_db(client->user_name, 0);
    server_event_user_logged_out(client->user_uuid);
    append_log_event(0, client->user_uuid, client->user_name);
    if (client->user_name)
        free(client->user_name);
    if (client->user_uuid)
        free(client->user_uuid);
    client->user_status = 0;
    client->is_logged_in = false;
    client->is_temp_logged_in = true;
}
