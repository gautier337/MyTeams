##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Xavier VINCENT - Hugo DUBOIS - Gautier BONHUR
##

SERVER_NAME			= 			myteams_server
CLIENT_NAME			=			myteams_cli
TEST_NAME			=			unit_tests

SERVER_MAIN			=			$(addprefix src/server/,					\
									main.c									\
								)

CLIENT_MAIN			=			$(addprefix src/client/,					\
									main.c									\
								)

SRC_SERVER			=			$(addprefix src/server/,					\
									commands/command_manager.c				\
									commands/create.c						\
									commands/help.c							\
									commands/info.c							\
									commands/list.c							\
									commands/login.c						\
									commands/logout.c						\
									commands/messages.c						\
									commands/send.c						    \
									commands/subscribe.c				    \
									commands/subscribed.c				    \
									commands/unsubscribe.c				    \
									commands/use.c							\
									commands/user.c							\
									commands/users.c						\
									database/channels.c						\
									database/infos_from_uuid.c				\
									database/load_user.c					\
									database/load_users.c					\
									database/replies.c						\
									database/teams.c						\
									database/threads.c						\
									database/users.c						\
									client.c								\
									connection.c							\
									create_errors.c							\
									events.c								\
									init.c									\
									loop.c									\
									notifications.c							\
									log_notifications.c      		        \
									reply_notifications.c      		        \
									subscribed_errors.c						\
									server.c								\
								)

SRC_CLIENT			=			$(addprefix src/client/,					\
									commands/create.c						\
									commands/help.c							\
									commands/info.c							\
									commands/list.c							\
									commands/login.c						\
									commands/logout.c						\
									commands/messages.c						\
									commands/subscribe.c			        \
									commands/subscribed.c			        \
									commands/unsubscribe.c			        \
									commands/use.c							\
									commands/user.c							\
									commands/users.c						\
									commands/send.c						    \
									api_errors.c							\
									events.c								\
									init.c									\
									loop.c 									\
									notifications.c							\
									server_response.c 						\
									subscribed_errors.c 					\
								)

SRC					=			$(addprefix src/,							\
									tools/file/append.c						\
									tools/file/directory.c					\
									tools/file/read.c						\
									tools/file/write.c						\
									tools/check_context.c					\
									tools/clear_pointer.c					\
									tools/context.c							\
									tools/dir.c								\
									tools/does_exist.c						\
									tools/error.c							\
									tools/list_output.c						\
									tools/parse_client_data.c 				\
									tools/parsing_sizes.c					\
									tools/parsing.c							\
									tools/read_from_fd.c					\
									tools/replace_str.c						\
									tools/send.c							\
									tools/server_list.c						\
									tools/socket.c							\
									tools/uuid.c							\
									tools/write_to_fd.c						\
									tools/timestamp.c						\
								)

SRC_TESTS			=			$(addprefix tests/,							\
								)

SRC_TESTS			+=			$(SRC_SERV) $(SRC_CLIENT) $(SRC)

OBJ_SERVER_MAIN		=			$(SERVER_MAIN:.c=.o)
OBJ_CLIENT_MAIN		=			$(CLIENT_MAIN:.c=.o)
OBJ_SERVER			=			$(SRC_SERVER:.c=.o)
OBJ_CLIENT			=			$(SRC_CLIENT:.c=.o)
OBJ					=			$(SRC:.c=.o)
OBJ_TESTS			=			$(SRC_TESTS:.c=.o)

CC					=			gcc
RM					=			rm -f
CFLAGS				+=			-Iinclude -Wall -Wextra
LDFLAGS				=			-Llibs -lmy -Llibs/myteams -lmyteams -luuid
CRITERION			=			--coverage -lcriterion

COMPILING_LIBS		=			"*******  COMPILING LIBS.  *******"
LIBS_COMPILED		=			"*******   LIBS COMPILED   *******"
COMPILING_SRCS		=			"*******  COMPILING SRCS.  *******"
SRCS_COMPILED		=			"*******   SRCS COMPILED   *******"
COMPILING_SERVER	=			"******* COMPILING SERVER. *******"
SERVER_COMPILED		=			"*******  SERVER COMPILED  *******"
COMPILING_CLIENT	=			"******* COMPILING CLIENT. *******"
CLIENT_COMPILED		=			"*******  CLIENT COMPILED  *******"
COMPILING_TESTS		=			"*******  COMPILING TESTS  *******"
TESTS_COMPILED		=			"*******  TESTS COMPILED.  *******"
CLEANING			=			"*******     CLEANING.     *******"
CLEANED				=			"*******  CLEAN COMPLETED  *******"
TESTING				=			"*******      TESTING.     *******"
TESTED				=			"*******  TESTS FINISHED.  *******"

all: $(SERVER_NAME) $(CLIENT_NAME)

libs:
	@echo $(COMPILING_LIBS)
	@make -C libs
	@echo $(LIBS_COMPILED)

$(SERVER_NAME): libs $(OBJ_SERVER) $(OBJ) $(OBJ_SERVER_MAIN)
	@echo $(COMPILING_SERVER)
	@$(CC) -o $(SERVER_NAME) $(OBJ_SERVER_MAIN) $(OBJ_SERVER) $(OBJ) $(LDFLAGS)
	@echo $(SERVER_COMPILED)

$(CLIENT_NAME): libs $(OBJ_CLIENT) $(OBJ) $(OBJ_CLIENT_MAIN)
	@echo $(COMPILING_CLIENT)
	@$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT_MAIN) $(OBJ_CLIENT) $(OBJ) $(LDFLAGS)
	@echo $(CLIENT_COMPILED)

tests_run: $(OBJ_TESTS)
	@echo $(COMPILING_LIBS)
	@make -C libs
	@echo $(LIBS_COMPILED)
	@echo $(COMPILING_TESTS)
	@$(CC) -o $(TEST_NAME) $(OBJ_TESTS) $(LDFLAGS) $(CRITERION)
	@echo $(TESTS_COMPILED)
	@echo $(TESTING)
	@./$(TEST_NAME)
	@echo $(TESTED)

clean:
	@echo $(CLEANING)
	@$(RM) $(OBJ_SERVER_MAIN) $(OBJ_CLIENT_MAIN)
	@$(RM) $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ)
	@$(RM) $(OBJ_TESTS)
	@make clean -C libs
	@echo $(CLEANED)

fclean: clean
	@$(RM) $(SERVER_NAME) $(CLIENT_NAME)
	@$(RM) $(TEST_NAME)
	@make fclean -C libs

re: fclean all

.PHONY: all libs server client tests_run clean fclean export re
