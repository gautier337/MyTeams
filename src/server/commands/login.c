/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** login.c
*/

#include "myteams.h"

void copy_user_data_to_struct(client_t *client, const char *user_name,
    const char *user_uuid, int status)
{
    if (!client || !user_name || !user_uuid)
        exit_error("copy_user_data_to_struct()");
    client->user_name = strdup(user_name);
    client->user_uuid = strdup(user_uuid);
    client->user_status = status;
    client->is_logged_in = status == 1 ? true : false;
}

char *append_user(const char *user_name)
{
    char *uuid = generate_uuid();

    if (!user_name || !uuid)
        exit_error("append_user()");
    append_user_to_db(user_name, uuid, 1);
    server_event_user_created((const char *)uuid, user_name);
    return uuid;
}

void handle_errors_login(client_t *client, const char **params)
{
    if (!client || !params)
        return;
    if (!params[1] || my_arrlen((char **)params) != 2)
        return send_to_user(client, API_INVALID_SYNTAX);
    if (client->is_logged_in)
        return send_to_user(client, API_METHOD_NOT_ALLOWED);
}

void handle_user_login(char *user_name)
{
    char **user_data = NULL;
    char *user_uuid = NULL;

    if (replace_str(user_name) && is_user_in_db(user_name)) {
        update_user_status_in_db(user_name, 1);
        user_data = load_user_from_db(user_name);
        user_uuid = strdup(user_data[1]);
    } else
        user_uuid = append_user(user_name);
    server_event_user_logged_in(user_uuid);
    append_log_event(1, user_uuid, user_name);
    if (user_data)
        free_array(user_data);
    free(user_uuid);
}

void login_command(server_t *server, client_t *client, const char **params)
{
    char **user = NULL;
    char *user_name = NULL;

    if (!server || !client || !params)
        exit_error("login_command()");
    if (!params[1] || my_arrlen((char **)params) != 2 || client->is_logged_in)
        return handle_errors_login(client, params);
    user_name = strdup(params[1]);
    handle_user_login(user_name);
    user = load_user_from_db(user_name);
    copy_user_data_to_struct(client, user[0], user[1], atoi(user[2]));
    free_array(user);
    free(user_name);
}
