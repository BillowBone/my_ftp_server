/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** listing.c
*/

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "server.h"

void exec_ls(client_t *client, char **args)
{
    int wait_pid = 0;
    pid_t pid;

    write(client->socket, "150 ", 4);
    pid = fork();
    if (pid == 0) {
        dup2(client->socket, 1);
        execve("/bin/ls", args, NULL);
        exit(0);
    }
    pid = wait(&wait_pid);
    write(client->socket, "\r\n", 2);
    client->response = my_strdup("226 Closing data connection.\r\n");
}

void listing(client_t *client)
{
    char **args = calloc(2, sizeof(char *));

    args[0] = my_strdup("/bin/ls");
    args[1] = NULL;
    chdir(client->current_dir);
    if (strlen(client->request) == 6) {
        exec_ls(client, args);
    }
    if (strlen(client->request) > 6) {
        char *path = parse_path(client->request, 2);
        if (chdir(path) == -1) {
            client->response = my_strdup("500 This path doesn't exists!\r\n");
            free(path);
            return;
        }
        exec_ls(client, args);
        free(path);
    }
    free(args[0]);
    free(args);
}