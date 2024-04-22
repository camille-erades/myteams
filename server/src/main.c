/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-clement.monnoire
** File description:
** main
*/

#include "server.h"

static int print_help(void)
{
    printf("USAGE: ./myteams_server port\n\n  \
    port is the port number on which the server socket listens.\n");
    return 0;
}

int main(int argc, char **argv)
{
    int port = 0;

    if (argc != 2)
        return 84;
    if (!strcmp(argv[1], "-help"))
        return print_help();
    port = atoi(argv[1]);
    if (port <= 1024)
        return 84;
    start_server(port);
    return 0;
}
