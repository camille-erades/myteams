/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** help
*/

#include "client.h"

void get_help(void)
{
    printf("/help : show help\n/login [“user_name”] : set");
    printf(" the user_name used by client\n");
    printf("/logout : disconnect client from the server\n");
    printf("/users : get the list of all users \
    that exist on the domain\n");
    printf("/user [“user_uuid”] : get details about\
    the requested user\n");
    printf("/send [“user_uuid”] [“message_body”] :\
    send a message to specific user\n");
    printf("/messages [“user_uuid”] : list all messages\
    exchanged with the specified user\n");
    printf("/subscribe [“team_uuid”] : subscribe to the\
    events of a team and its sub directories (enable reception of all\
    events from a team)\n");
    printf("/subscribed ?[“team_uuid”] : list all subscribed\
    teams or list all users subscribed to a team\n");
    printf("/unsubscribe [“team_uuid”] :\
    unsubscribe from a team\n");
}
