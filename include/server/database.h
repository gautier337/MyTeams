/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** database
*/

#ifndef DATABASE_H_
    #define DATABASE_H_

    // Channels
    bool is_channel_in_team(
        const char *team_uuid, const char *team_name);
    char *create_channel(
        const char *team_uuid,
        const char *channel_name,
        const char *channel_description
    );

    // Infos from UUID
    char *get_team_infos_from_uuid(char *team_uuid);
    char *get_user_infos_from_uuid(const char *user_uuid);

    // Load user
    char **load_user_from_db(const char *user_name);

    // Load users
    char **load_users_from_db(void);

    // Replies
    char **create_reply(
        client_t *client,
        const char *reply_body
    );

    // Teams
    bool check_if_user_is_subscribe_to_the_team(
        char *team_uuid, char *user_uuid);
    bool is_team_in_db(const char *team_name);
    bool return_close_and_free(bool ret, DIR *dir, char *filename);
    char *create_team(const char *team_name, const char *team_description);

    // Threads
    bool is_thread_in_channel(
        const char *team_uuid,
        const char *channel_uuid,
        const char *thread_name
    );
    char **create_thread(
        client_t *client,
        const char *thread_name,
        const char *thread_message
    );

    // Users
    bool is_user_in_db(const char *user_name);
    bool is_uuid_in_db(const char *user_uuid);
    void append_user_to_db(
        const char *user_name, const char *user_uuid, int status);
    void update_user_status_in_db(const char *user_name, int status);

#endif /* !DATABASE_H_ */
