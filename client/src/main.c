/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** main
*/

#include "../include/client.h"

static void read_server(int *sockfd, client_t *client)
{
    int len = 0;
    char buff[MAX_BUFFER_LENGTH];

    len = recv(*sockfd, buff, MAX_BUFFER_LENGTH, 0);
    if (len <= 0) {
        *sockfd = -1;
        return;
    }
    buff[len] = '\0';
    exec_command(buff, client);
}

static void read_client(client_t *client, int sockfd)
{
    int len = 0;
    char *buffer = get_input(stdin);

    if (!strcmp(buffer, "/help\n"))
        get_help();
    else
        dprintf(sockfd, "%s", buffer);
    free(buffer);
}

static void run_cli(int sockfd, client_t *client)
{
    fd_set fds;

    while (run && sockfd != -1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(sockfd, &fds);
        if (select(sockfd + 1, &fds, NULL, NULL, NULL) < 0)
            break;
        if (FD_ISSET(STDIN_FILENO, &fds))
            read_client(client, sockfd);
        if (FD_ISSET(sockfd, &fds))
            read_server(&sockfd, client);
    }
}

static client_t *init_cli(void)
{
    client_t *client;

    client = malloc(sizeof(client_t));
    client->login = false;
    client->uuid = malloc(sizeof(char) * 37);
    return client;
}

int start_client(char *ip, int port)
{
    client_t *client = NULL;
    struct hostent *info;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr = {0};

    info = gethostbyname(ip);
    if (!info)
        return 84;
    client = init_cli();
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    run_cli(sockfd, client);
    free(client);
    return 0;
}

void handle_sigint(int sig)
{
    run = 0;
    (void) sig;
}

int main(int argc, char **argv)
{
    int port = 0;

    if (argc != 3)
        return 84;
    port = atoi(argv[2]);
    if (port < 1024)
        return 84;
    signal(SIGINT, handle_sigint);
    return start_client(argv[1], port);
}
