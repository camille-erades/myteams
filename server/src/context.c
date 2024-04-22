/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** context
*/

#include "server.h"

int count_context(char *context)
{
    int count = 0;

    for (int i = 0; context[i]; i++)
        if (context[i] == '/')
            count++;
    return count;
}

void define_context(client_t *client, char **cmd)
{
    client->context[0] = '\0';
    for (int i = 0; cmd && cmd[i] && i < 3; i++) {
        strcat(client->context, cmd[i]);
        strcat(client->context, "/");
    }
}
