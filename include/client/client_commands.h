/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** client_commands.h
*/

#ifndef CLIENT_COMMANDS_H_
    #define CLIENT_COMMANDS_H_

    // MyTeams
    #include "myteams.h"

    // Data
    typedef struct client_command_s {
        char *name;
        void (*function)(client_t *client,
            const char *response);
    } client_command_t;

    // Commands
    #define CLIENT_COMMANDS_COUNT 14

    #define CLIENT_COMMANDS {{                                              \
            "/create", &create_fn_client                                    \
        }, {                                                                \
            "/help", &help_client                                           \
        }, {                                                                \
            "/info", &info_client                                           \
        }, {                                                                \
            "/list", &list_client                                           \
        }, {                                                                \
            "/login", &login_client                                         \
        }, {                                                                \
            "/logout", &logout_client                                       \
        }, {                                                                \
            "/messages", &messages_client                                   \
        }, {                                                                \
            "/send", &send_client                                           \
        }, {                                                                \
            "/subscribe", &subscribe_client                                 \
        }, {                                                                \
            "/subscribed", &subscribed_client                               \
        }, {                                                                \
            "/unsubscribe", &unsubscribe_client                             \
        }, {                                                                \
            "/use", &use_client                                             \
        }, {                                                                \
            "/user", &user_client                                           \
        }, {                                                                \
            "/users", &users_client                                         \
        }, {                                                                \
            NULL, NULL                                                      \
        }                                                                   \
    }

    // Commands
    void create_fn_client(client_t *client, const char *response);
    void help_client(client_t *client, const char *response);
    void info_client(client_t *client, const char *response);
    void list_client(client_t *client, const char *response);
    void login_client(client_t *client, const char *response);
    void logout_client(client_t *client, const char *response);
    void messages_client(client_t *client, const char *response);
    void send_client(client_t *client, const char *response);
    void subscribe_client(client_t *client, const char *response);
    void subscribed_client(client_t *client, const char *response);
    void unsubscribe_client(client_t *client, const char *response);
    void use_client(client_t *client, const char *response);
    void user_client(client_t *client, const char *response);
    void users_client(client_t *client, const char *response);

#endif /* !CLIENT_COMMANDS_H_ */
