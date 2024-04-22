/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-clement.monnoire
** File description:
** server
*/

#include "server.h"

int get_server_socket(int port)
{
    int sockfd;
    int opt;
    struct sockaddr_in sock_in;

    opt = 1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return sockfd;
    sock_in.sin_port = htons(port);
    sock_in.sin_family = AF_INET;
    sock_in.sin_family = AF_INET;
    sock_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&sock_in,
        sizeof(sock_in)) < 0)
        return -1;
    if (listen(sockfd, MAX_CONNECTIONS) < 0)
        return -1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    return sockfd;
}

void manage_client(my_ftp_t *ftp)
{
    for (client_t *p = ftp->head; p; p = p->next) {
        if (FD_ISSET(p->clientfd, &ftp->read_fd_set))
            parse_command(p);
        if (p->next == ftp->head)
            break;
    }
}

static void reset_fd(my_ftp_t *ftp)
{
    FD_ZERO(&ftp->read_fd_set);
    FD_SET(ftp->masterfd, &ftp->read_fd_set);
    for (client_t *p = ftp->head; p; p = p->next) {
        if (p->clientfd > 0)
            FD_SET(p->clientfd, &ftp->read_fd_set);
        if (p->next == ftp->head)
            break;
    }
}

void server_loop(my_ftp_t *ftp)
{
    int client_sockfd;
    socklen_t client_len = sizeof(ftp->sock_in);

    while (run) {
        reset_fd(ftp);
        if (select(FD_SETSIZE, &ftp->read_fd_set, NULL, NULL, NULL) < 0)
            break;
        if (FD_ISSET(ftp->masterfd, &ftp->read_fd_set)) {
            client_sockfd = accept(ftp->masterfd,
                (struct sockaddr *)&ftp->sock_in, &client_len);
            create_new_client(ftp, client_sockfd);
        }
        manage_client(ftp);
    }
}

void handle_sigint(int sig)
{
    run = 0;
    (void) sig;
}

void start_server(int port)
{
    my_ftp_t ftp = {0};

    signal(SIGINT, handle_sigint);
    ftp.masterfd = get_server_socket(port);
    init_clients();
    server_loop(&ftp);
    close(ftp.masterfd);
}
