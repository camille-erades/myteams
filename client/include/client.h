/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <netinet/in.h>
    #include <signal.h>
    #include <arpa/inet.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <sys/socket.h>
    #include <sys/wait.h>
    #include <sys/time.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include "linux/limits.h"
    #include <sys/queue.h>
    #include <stddef.h>
    #include <uuid/uuid.h>
    #include "../../libs/myteams/logging_client.h"

    #define MAX_CONNECTIONS 10
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define MAX_BUFFER_LENGTH 1024

typedef struct client_s {
    bool login;
    char *uuid;
    char username[MAX_NAME_LENGTH];
} client_t;

typedef struct command_s {
    char *name;
    void (*command)(client_t *, char **);
} command_t;

static volatile sig_atomic_t run = 1;

int start_client(char *, int);
char *get_input(FILE *fd);
char **my_quote_to_wolrd_array(char *str);
char **my_str_to_word_array(char *str, char *separator);
void destroy_tab(char **tab);
void exec_command(char *buffer, client_t *client);

// command

void log_out(client_t *client, char **command);
void log_in(client_t *client, char **command);
void send_msg(client_t *client, char **command);
void print_users(client_t *client, char **command);
void print_users(client_t *client, char **command);
void print_user(client_t *client, char **command);
void log_out(client_t *client, char **command);
void log_in(client_t *client, char **command);
void create_event(client_t *client, char **cmd);
void list_event(client_t *client, char **cmd);
void info_event(client_t *client, char **cmd);
void messages(client_t *client, char **command);
void error_event(client_t *client, char **command);
void unsubscribe(client_t *client, char **command);
void subscribe(client_t *client, char **command);
void subscribed(client_t *client, char **command);
void get_help(void);

#endif /* !CLIENT_H_ */
