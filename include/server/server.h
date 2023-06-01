/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    // MyTeams
    #include "myteams.h"

    // Client
    int handle_client(server_t *server, client_t *client);
    void handle_clients(server_t *server, client_t *clients,
        int nb_clients, fd_set read_fds);
    void remove_disconnected_clients(client_t *clients, int *nb_clients);

    // Connection
    int accept_connection(int sockfd);
    void accept_new_connection(
        server_t *server, client_t *clients, int *nb_clients, int *max_fd);

    // Create Errors
    bool handle_errors_create(client_t *c, const char **params);

    // Events
    void append_log_event(int status, char *user_uuid, char *user_name);

    // Init
    server_t *create_server(int port);
    void init_queue(int sockfd);
    void init_fd_set(
        int sockfd, client_t *clients, int nb_clients, fd_set *read_fds);

    // Loop
    void connection_loop(server_t *server);

    // Notifications
    void handle_notifications(client_t *clients);
    void handle_notifications_log(client_t *clients);
    void handle_notifications_reply(client_t *clients);

    // Server
    int myteams_server(int server_port);

    // Subscribed Errors
    bool handle_subscribed_errors_users(
        client_t *client, const char *team_uuid);

#endif /* !SERVER_H_ */
