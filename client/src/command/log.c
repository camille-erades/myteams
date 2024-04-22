/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** log.c
*/

#include "../include/client.h"

void log_out(client_t *client, char **command)
{
    client->login = false;
    client_event_logged_out(client->uuid, client->username);
    client->username[0] = '\0';
    if (client->uuid) {
        free(client->uuid);
        client->uuid = NULL;
    }
}

void log_in(client_t *client, char **command)
{
    strcpy(client->username, command[1]);
    client->uuid = malloc(sizeof(char) * (strlen(command[1] + 1)));
    strcpy(client->uuid, command[1]);
    client_event_logged_in(client->uuid, client->username);
}
