/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** subs
*/

#include "server.h"

void subscribe(client_t *client, char **command)
{
    char *line;
    char path[4096];
    char **teams_id;
    FILE *teams_subscription;

    teams_id = get_file("./server/save/teams/teams_id_list.txt");
    sprintf(path, "%s%steams_subscription.txt", CLIENT_SAVE, client->uuid);
    teams_subscription = fopen(path, "a+");
    for (int i = 0; teams_id && teams_id[i]; i++) {
        if (strcmp(teams_id[i], command[1])) {
            fprintf(teams_subscription, command[1]);
            return;
        }
    }
    destroy_tab(teams_id);
    fclose(teams_subscription);
}

void subscribed(client_t *client, char **command)
{
    char path[4096];
    char buffer[4096];
    FILE *teams_subscription;

    sprintf(path, "%s%steams_subscription.txt", CLIENT_SAVE, client->uuid);
    teams_subscription = fopen(path, "r");
    if (teams_subscription == NULL) {
        printf("Error opening teams_subscription.txt\n");
        return;
    }
    if (command[1] == NULL) {
        printf("Teams subscribed by client %s:\n", client->uuid);
        while (fgets(buffer, sizeof(buffer), teams_subscription) != NULL)
            printf("%s", buffer);
    } else {
        printf("Users subscribed to team %s:\n", command[1]);
    }
    fclose(teams_subscription);
}

void unsubscribe(client_t *client, char **command)
{
    char path[4096];
    char buffer[4096];
    FILE *teams_subscription;
    FILE *temp_file;

    sprintf(path, "%s%steams_subscription.txt", CLIENT_SAVE, client->uuid);
    teams_subscription = fopen(path, "r");
    temp_file = fopen("./temp.txt", "w");
    if (teams_subscription == NULL || temp_file == NULL) {
        printf("Error opening files\n");
        return;
    }
    while (fgets(buffer, sizeof(buffer), teams_subscription) != NULL)
        if (strstr(buffer, command[1]) == NULL)
            fprintf(temp_file, "%s", buffer);
    fclose(teams_subscription);
    fclose(temp_file);
    remove(path);
    rename("./temp.txt", path);
}
