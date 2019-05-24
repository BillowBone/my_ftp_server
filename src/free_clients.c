/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** free_clients.c
*/

#include <unistd.h>
#include "server.h"

void free_clients(list_t *my_clients)
{
    client_t *current = my_clients->first;

    while (current->next != NULL) {
        free(current->request);
        free(current->response);
        current = current->next;
    }
    free(current->request);
    free(current->response);
    free(current);
    free(my_clients);
}