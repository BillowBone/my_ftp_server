/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** read_clients.c
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

char *add_new_char(char *str)
{
    char *new = NULL;

    if (strlen(str) < 1)
        return (str);
    new = calloc(strlen(str) + 2, sizeof(char));
    if (!new)
        exit(84);
    strcpy(new, str);
    free(str);
    return (new);
}

void end_reading(client_t *current, int len, int cmp)
{
    if (current->has_requested == 1 && len > 2 && cmp == 0) {
        interpret_request(current);
        current->current_char_read = 0;
        free(current->request);
        char *new = calloc(2, sizeof(char));
        if (!new)
            exit(84);
        current->request = new;
    }
}

void process_new_char(client_t *current, char c)
{
    current->request = add_new_char(current->request);
    current->request[current->current_char_read] = c;
    current->request[current->current_char_read + 1] = 0;
    current->current_char_read++;
}

void read_requests(client_t *crt, fd_set reads)
{
    char c = 0;
    int cmp = 0;
    int len = 0;

    if (FD_ISSET(crt->socket, &reads) == 1 && crt->first_contact != 0) {
        while (1) {
            if (read(crt->socket, &c, 1) <= 0)
                break;
            else if (crt->has_requested == 0)
                crt->has_requested = 1;
            process_new_char(crt, c);
            len = strlen(crt->request);
            if (len > 2)
                cmp = strcmp(crt->request + len - 2, "\r\n\0");
            if (len > 2 && cmp == 0)
                break;
        }
        end_reading(crt, len, cmp);
    }
}