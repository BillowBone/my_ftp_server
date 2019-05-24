/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** close_clients.c
*/

#include <unistd.h>
#include "server.h"

void close_clients(list_t *my_clients)
{
    client_t *current = my_clients->first;

    while (current) {
        close(current->socket);
        current = current->next;
    }
}