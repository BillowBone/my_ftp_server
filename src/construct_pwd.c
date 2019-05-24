/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** construct_pwd.c
*/

#include <string.h>
#include "server.h"

void construct_pwd(client_t *current)
{
    int len = strlen(current->current_dir);
    current->response = calloc(len + 8, sizeof(char));
    current->response = strcat(current->response, "257 ");
    current->response = strcat(current->response, current->current_dir);
    current->response = strcat(current->response, "\r\n");
}