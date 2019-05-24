/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** get_bigger_socket.c
*/

#include <unistd.h>
#include "server.h"

int get_bigger_socket(list_t *my_clients, int srvr_sckt)
{
    int bigger = 0;
    client_t *current = NULL;

    if (my_clients) {
        current = my_clients->first;
        while (current) {
            if (current->socket > bigger)
                bigger = current->socket;
            current = current->next;
        }
    }
    if (srvr_sckt > bigger)
        bigger = srvr_sckt;
    return (bigger);
}