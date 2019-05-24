/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** change_working_directory.c
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

void change_working_directory(client_t *current)
{
    char *path = parse_path(current->request, 1);

    if (chdir(path) == 0) {
        getcwd(current->current_dir, sizeof(current->current_dir));
    } else {
        free(current->response);
        current->response = my_strdup("550 Can't access this"
                                        " working directory!\r\n");
    }
    free(path);
}