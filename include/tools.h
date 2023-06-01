/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** tools.c
*/

#ifndef TOOLS_H_
    #define TOOLS_H_

    // MyTeams
    #include "myteams.h"

    // File
        // Append
        int append_file(const char *filename, const char *content);

        // Read
        char *read_file(const char *filename);

        // Write
        void write_file(const char *filename, const char *content);

        // Create Directories
        bool create_directory_if_not_exists(const char *dir);

        // File Exists
        bool file_exists(const char *path);

        // Directory Exists
        bool directory_exists(const char *dir_path);

    // Check Context
    bool check_context(client_t *client);

    // Clear Pointer
    void clear_pointer(void **ptr);

    // Context
    char *get_dir_from_context(
        char *team_uuid,
        char *channel_uuid,
        char *thread_uuid
    );
    char *get_infos_from_context(
        char *team_uuid,
        char *channel_uuid,
        char *thread_uuid
    );

    // Dir
    bool is_empty_dir(DIR *dir);

    // Does Exist
    bool does_team_exist(const char *team_uuid);
    bool does_channel_exist(const char *team_uuid, const char *channel_uuid);
    bool does_thread_exist(
        const char *team_uuid,
        const char *channel_uuid,
        const char *thread_uuid
    );

    // Error
    void exit_error(char *str);
    DIR *get_dir_and_error(client_t *client,const char *folder);
    void send_list_output(client_t *client, char *data);

    // List Output
    void add_line_to_data(
        char **data, char *line, enum context_type default_context);
    char *create_line_from_thread_file(client_t *client,
        const char *thread_uuid, char *file_content);
    char *get_data_from_folder_file(char *dir, char *file);

    // Parse Client
    void parse_thread_client(char *line);
    void parse_reply_client(char *line);

    // Parsing Sizes
    int get_nb_args(char *buffer);
    int *get_args_size(int nb_args, char *buffer);

    // Parsing
    char **my_parse_args(char *buffer);

    // Read from FD
    char *read_from_fd(int fd, size_t size);

    // Replace
    char *replace_str(char *string);

    // Send
    char *msprintf(const char *format, ...);
    void send_to_user(client_t *client, char *buffer);
    void send_invalid_context(
        client_t *client,
        enum context_type context,
        char *api_code,
        char *data
    );

    // Server List
    char *create_line_output_from_team(const char *team_uuid);
    char *create_line_output_from_channel(
        client_t *client,
        const char *channel_uuid
    );
    char *create_line_output_from_thread(
        client_t *client,
        const char *thread_uuid
    );
    char *create_line_output_from_reply(
        client_t *client,
        const char *reply_uuid
    );

    // Socket
    void close_socket(int sockfd);

    // Timestamp
    time_t get_timestamp(void);
    char *timestamp_to_str(time_t timestamp);
    time_t parse_timestamp(const char *timestamp_str);

    // UUID
    char *generate_uuid(void);

    // Write to FD
    void write_to_fd(int fd, const char *buffer);

#endif /* !TOOLS_H_ */
