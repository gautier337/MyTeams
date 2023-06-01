/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** myteams.h
*/

#ifndef MYTEAMS_H_
    #define MYTEAMS_H_

    // Libs
    #include "../libs/my/my.h"
    #include "../libs/my_printf/my_printf.h"
    #include "../libs/myteams/logging_client.h"
    #include "../libs/myteams/logging_server.h"

    // C
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <stddef.h>
    #include <sys/select.h>
    #include <string.h>
    #include <errno.h>
    #include <stdbool.h>
    #include <dirent.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <uuid/uuid.h>

    // Data
    typedef struct server_s {
        int port;
        int sockfd;
    } server_t;

    enum context_type {
        NO_CONTEXT,
        TEAM,
        CHANNEL,
        THREAD
    };

    typedef struct context_s {
        enum context_type type;
        char *team_uuid;
        char *channel_uuid;
        char *thread_uuid;
    } context_t;

    typedef struct client_s {
        int sockfd;
        char *buffer;
        bool is_connected;
        bool is_logged_in;
        bool is_temp_logged_in;
        char *user_name;
        char *user_uuid;
        int user_status;
        context_t *context;
    } client_t;

    #define SUCCESS 0
    #define ERROR 84
    #define BACKLOG_SIZE 10
    #define READ_BUFFER_SIZE (size_t) 1024
    #define MAX_CLIENTS 30
    #define PING_TIMEOUT 100
    #define MAX_BODY_LENGTH 512
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_NAME_LENGTH 32

    #define USERS_LIST_PATH "data/users.csv"

    // API Codes
    #define API_SUCCESS "200\r\n"
    #define API_NO_CONTENT "204\r\n"
    #define API_NOTIFIED "205\r\n"
    #define API_LOG_EVENT "206\r\n"
    #define API_REPLY_EVENT "207\r\n"
    #define API_INVALID_SYNTAX "400\r\n"
    #define API_UNAUTHORIZED "401\r\n"
    #define API_NOT_FOUND "404\r\n"
    #define API_METHOD_NOT_ALLOWED "405\r\n"
    #define API_CONFLICT "409\r\n"
    #define API_INVALID_CONTEXT "428\r\n"
    #define API_INTERNAL_ERROR "500\r\n"

    // Colors
    #define KNRM "\x1B[0m"
    #define KRED "\x1B[31m"
    #define KGRN "\x1B[32m"
    #define KYEL "\x1B[33m"
    #define KBLU "\x1B[34m"
    #define KMAG "\x1B[35m"
    #define KCYN "\x1B[36m"
    #define KWHT "\x1B[37m"

    // Tools
    #include "tools.h"

    // Server
    #include "server/commands.h"
    #include "server/database.h"
    #include "server/server.h"

    // Client
    #include "client/client_commands.h"
    #include "client/client.h"

#endif /*MYTEAMS_H_*/
