/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** delete_client.c
*/

#include <unistd.h>
#include "server.h"

void free_struct(client_t *current)
{
    close(current->socket);
    free(current->request);
    free(current);
}

int which_delete(list_t *my_clients, client_t *current, client_t *previous)
{
    if (!previous && current->quitting == 1) {
        client_t *del = my_clients->first;
        my_clients->first = my_clients->first->next;
        free_struct(del);
        return (1);
    } else if (current->next && current->quitting == 1) {
        previous->next = current->next;
        free_struct(current);
        return (1);
    } else if (!current->next && current->quitting == 1) {
        previous->next = NULL;
        free_struct(current);
        return (1);
    }
    return (0);
}

int delete_client(list_t *my_clients)
{
    client_t *previous = NULL;
    client_t *current = my_clients->first;

    if (current) {
        while (current->next && current->quitting != 0) {
            previous = current;
            current = current->next;
        }
        return (which_delete(my_clients, current, previous));
    }
    return (0);
}

void check_quitting_clients(list_t *my_clients)
{
    while (delete_client(my_clients));
}