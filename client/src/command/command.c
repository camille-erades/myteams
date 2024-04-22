/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** command
*/

#include "../include/client.h"

command_t command_list[] = {
    {"/login", log_in},
    {"/logout", log_out},
    {"/send", send_msg},
    {"/users", print_users},
    {"/user", print_user},
    {"/messages", messages},
    {"/create", create_event},
    {"/list", list_event},
    {"/info", info_event},
    {"/subscribe", subscribe},
    {"/unsubscribe", unsubscribe},
    {"/subscribed", subscribed},
    {"/error", error_event}
};

void messages(client_t *client, char **command)
{
    printf("messages");
}

void send_msg(client_t *client, char **command)
{
    client_event_private_message_received(command[0], command[1]);
}

char *get_cmd(char *str)
{
    int i = 0;
    char *cmd = NULL;

    while (str[i] && str[i] != ' ')
        i++;
    cmd = malloc(sizeof(char) * (i + 1));
    strncpy(cmd, str, i);
    cmd[i] = '\0';
    return cmd;
}

void exec_command(char *buffer, client_t *client)
{
    char **argv;
    char *command;

    argv = my_quote_to_wolrd_array(buffer);
    command = get_cmd(buffer);
    for (int i = 0; i < 13; i++)
        if (!strcmp(command, command_list[i].name))
            command_list[i].command(client, argv);
    free(command);
    destroy_tab(argv);
}
