/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** server_commands.h
*/

#ifndef SERVER_COMMANDS_H_
    #define SERVER_COMMANDS_H_

    // MyTeams
    #include "myteams.h"

    // Data
    typedef struct server_command_s {
        char *name;
        void (*function)(server_t *server, client_t *client,
            const char **params);
    } server_command_t;

    // Commands
    #define SERVER_COMMANDS_COUNT 14

    #define SERVER_COMMANDS {{                                              \
            "/create", &create_command,                                     \
        }, {                                                                \
            "/help", &help_command                                          \
        }, {                                                                \
            "/info", &info_command                                          \
        }, {                                                                \
            "/list", &list_command                                          \
        }, {                                                                \
            "/login", &login_command                                        \
        }, {                                                                \
            "/logout", &logout_command                                      \
        }, {                                                                \
            "/messages", &messages_command                                  \
        }, {                                                                \
            "/send", &send_command                                          \
        }, {                                                                \
            "/subscribe", &subscribe_command                                \
        }, {                                                                \
            "/subscribed", &subscribed_command                              \
        }, {                                                                \
            "/unsubscribe", &unsubscribe_command                            \
        }, {                                                                \
            "/use", &use_command                                            \
        }, {                                                                \
            "/user", &user_command                                          \
        }, {                                                                \
            "/users", &users_command                                        \
        }, {                                                                \
            NULL, NULL                                                      \
        }                                                                   \
    }

    // Functions
    void remove_crlf(char *str);
    void free_array(char **array);
    void send_to_user_with_state(client_t *client, int state, char *data);
    char *find_user_line(char *file_content, const char *user_uuid);

    // Commands
    void command_manager(server_t *server, client_t *client);
    void create_command(server_t *server, client_t *client,
        const char **params);
    void help_command(server_t *server, client_t *client,
        const char **params);
    void info_command(server_t *server, client_t *client,
        const char **params);
    void list_command(server_t *server, client_t *client,
        const char **params);
    void login_command(server_t *server, client_t *client,
        const char **params);
    void logout_command(server_t *server, client_t *client,
        const char **params);
    void messages_command(server_t *server, client_t *client,
        const char **params);
    void send_command(server_t *server, client_t *client,
        const char **params);
    void subscribe_command(server_t *server, client_t *client,
        const char **params);
    void subscribed_command(server_t *server, client_t *client,
        const char **params);
    void unsubscribe_command(server_t *server, client_t *client,
        const char **params);
    void use_command(server_t *server, client_t *client,
        const char **params);
    void user_command(server_t *server, client_t *client,
        const char **params);
    void users_command(server_t *server, client_t *client,
        const char **params);

#endif /* !SERVER_COMMANDS_H_ */
