/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/wait.h>
    #include <sys/time.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <signal.h>
    #include "../../libs/myteams/logging_server.h"
    #include <dirent.h>
    #include <uuid/uuid.h>
    #include "linux/limits.h"


    #define MAX_CONNECTIONS 10
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    #define CLIENT_SAVE "server/save/clients/"
    #define TEAM_SAVE "server/save/teams/"

typedef struct client_s {
    int clientfd;
    char username[32];
    char buffer[MAX_BODY_LENGTH];
    char context[PATH_MAX];
    bool is_connected;
    char *uuid;
    struct client_s *next;
} client_t;

typedef struct my_ftp_s {
    int masterfd;
    client_t *head;
    fd_set read_fd_set;
    struct sockaddr_in sock_in;
} my_ftp_t;

typedef struct command_s {
    char *name;
    void (*command)(client_t *, char **);
} command_t;

static volatile sig_atomic_t run = 1;

// server function
void start_server(int port);
void server_loop(my_ftp_t *ftp);
int get_server_socket(int port);

// client function
void create_new_client(my_ftp_t *ftp, int fd);
void init_clients(void);

// lib function
char **my_quote_to_wolrd_array(char *str);
char **my_str_to_word_array(char *str, char *separator);
void destroy_tab(char **tab);
char **get_file(char *path);

// command
void parse_command(client_t *client);
void exec_command(client_t *client, char *cmd);
void close_user(client_t *client, char **argv);
void log_out(client_t *client, char **cmd);
void log_in(client_t *client, char **cmd);
void send_msg(client_t *client, char **cmd);
void print_users(client_t *client, char **cmd);
void print_this_user(client_t *client, char **cmd);
void define_context(client_t *client, char **cmd);
void create(client_t *client, char **cmd);
void list(client_t *client, char **cmd);
int count_context(char *context);
void subscribe(client_t *client, char **command);
void unsubscribe(client_t *client, char **command);
void subscribed(client_t *client, char **command);
#endif /* !SERVER_H_ */
