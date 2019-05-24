/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** write_clients.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"

void end_write(client_t *crt)
{
    if (crt->response[crt->current_char_write] == 0) {
        crt->current_char_write = 0;
        if (crt->first_contact == 0)
            crt->first_contact = 1;
        free(crt->response);
    }
    crt->has_requested = 0;
}

void write_responses(client_t *crt, fd_set requests_write)
{
    int len = 0;
    int crt_char = 0;

    if (FD_ISSET(crt->socket, &requests_write) == 1) {
        if (crt->has_requested == 1 || crt->first_contact == 0) {
            len = strlen(crt->response);
            for (; crt->current_char_write < len; crt->current_char_write++) {
                crt_char = crt->current_char_write;
                if (write(crt->socket, &crt->response[crt_char], 1) < 1)
                    break;
            }
            end_write(crt);
        }
    }
}