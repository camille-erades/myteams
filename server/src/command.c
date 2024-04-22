/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** command
*/

#include "server.h"

command_t command_list[] = {
    {"/login", log_in},
    {"/logout", log_out},
    {"/send", send_msg},
    {"/users", print_users},
    {"/user", print_this_user},
    {"/use", define_context},
    {"/create", create},
    {"/list", list},
    {"/subscribe", subscribe},
    {"/subscribed", subscribed},
    {"/unsubscribe", unsubscribe}
};

char *get_cmd(char *str)
{
    int i = 0;
    char *cmd = NULL;

    while (str[i] && str[i] != ' ' && str[i] != '\n')
        i++;
    cmd = malloc(sizeof(char) * (i + 1));
    strncpy(cmd, str, i);
    cmd[i] = '\0';
    return cmd;
}

void exec_command(client_t *client, char *command)
{
    char **argv = NULL;

    argv = my_quote_to_wolrd_array(client->buffer);
    for (int i = 0; i < 8; i++) {
        if (!strcmp(command, command_list[i].name))
            command_list[i].command(client, argv);
    }
    destroy_tab(argv);
}

void parse_command(client_t *client)
{
    ssize_t pos;
    char *cmd;

    pos = read(client->clientfd, client->buffer, MAX_BODY_LENGTH);
    if (pos == 0)
        return close_user(client, NULL);
    client->buffer[pos] = '\0';
    cmd = get_cmd(client->buffer);
    if (strcmp(cmd, "/login") && client->is_connected == false)
        dprintf(client->clientfd, "/error \"login\"");
    else
        exec_command(client, cmd);
}
