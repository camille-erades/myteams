/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** context
*/

#include "client.h"

void create_event(client_t *client, char **cmd)
{
    int index = atoi(cmd[0]);

    switch (index) {
    case 0:
        client_event_team_created(cmd[1], cmd[2], cmd[3]);
        break;
    case 1:
        client_event_channel_created(cmd[1], cmd[2], cmd[3]);
        break;
    case 2:
        break;
    default:
        break;
    }
}

void list_event(client_t *client, char **cmd)
{
    int index = atoi(cmd[0]);

    switch (index) {
    case 0:
        client_print_teams(cmd[1], cmd[2], cmd[3]);
        break;
    case 1:
        client_team_print_channels(cmd[1], cmd[2], cmd[3]);
        break;
    case 2:
        break;
    default:
        break;
    }
}

void info_event(client_t *client, char **cmd)
{
}
