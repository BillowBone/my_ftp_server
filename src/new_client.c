/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** new_client.c
*/

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"

client_t *init_client(int socket, char *home)
{
    client_t *new = calloc(1, sizeof(client_t));
    if (!new)
        exit(84);
    new->socket = socket;
    void *ptr = calloc(2, sizeof(char));
    if (!ptr)
        exit(84);
    new->request = ptr;
    memset(new->request, 0, 2);
    new->response = my_strdup("220 Welcome to my FTP server!\r\n\0");
    strcpy(new->current_dir, home);
    new->current_char_read = 0;
    new->current_char_write = 0;
    new->has_requested = 0;
    new->first_contact = 0;
    new->username = 0;
    new->password = 0;
    new->quitting = 0;
    new->next = NULL;
    return (new);
}

list_t *insert_client(list_t *my_clients, int socket, char *home)
{
    client_t *new = init_client(socket, home);
    if (!my_clients) {
        my_clients = calloc(1, sizeof(list_t));
        my_clients->first = new;
    } else if (!my_clients->first) {
        my_clients->first = new;
    } else {
        client_t *current = my_clients->first;
        while (current->next != NULL)
            current = current->next;
        current->next = new;
    }
    return (my_clients);
}

list_t *new_client(int socket, list_t *clients, char *home)
{
    struct sockaddr_in my_addr2 = { 0 };
    int sinsize = sizeof(my_addr2);

    int socket_tmp = accept(socket, (struct sockaddr *)&my_addr2, &sinsize);
    clients = insert_client(clients, socket_tmp, home);
    return (clients);
}