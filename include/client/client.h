/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** client.h
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    // MyTeams
    #include "myteams.h"

    // API Errors
    bool handle_api_errors_create(
        const char *response, enum context_type context);
    bool handle_api_errors_list(const char *response);
    bool handle_api_errors_info(const char *response);

    // Events
    bool handle_log_events(client_t *client, char *response);
    bool handle_reply_events(client_t *client, char *response);

    // Init
    client_t *create_client(char *ip, int port);

    // Loop
    void client_loop(client_t *client);

    // Main
    void print_client_usage(void);
    int get_port(char *port);
    int client(char *ip, char *port);

    // Notifications
    void handle_notification(client_t *client, char *response);

    // Server response
    void handle_server_response(client_t *client, char *response);

    // Subscribed Errors
    bool handle_subscribed_errors(client_t *client, int context, char *data);

#endif /* !CLIENT_H_ */
