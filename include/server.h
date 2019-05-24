/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - FTP Server
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

#include <stdlib.h>
#include <sys/time.h>

typedef struct client_s {
    int socket;
    char *request;
    char *response;
    char current_dir[1024];
    int current_char_read;
    int current_char_write;
    int has_requested;
    int first_contact;
    int username;
    int password;
    int quitting;
    struct client_s *next;
} client_t;

typedef struct list_s {
    client_t *first;
} list_t;

int create_socket();
void bind_server(int socket, char *port);
void open_server(int server_socket);
client_t *init_client(int socket, char *home);
list_t *insert_client(list_t *my_clients, int socket, char *home);
list_t *new_client(int socket, list_t *clients, char *home);
void free_clients(list_t *my_clients);
void read_requests(client_t *current, fd_set requests_read);
void write_responses(client_t *crt, fd_set requests_write);
void close_clients(list_t *my_clients);
void server(int socket, list_t *clients, char *path);
void interpret_request(client_t *current);
void verify_args(int argc, char *argv[]);
void check_quitting_clients(list_t *my_clients);
void display_help(void);
char *my_strdup(char *str);
int get_bigger_socket(list_t *my_clients, int srvr_sckt);
void change_working_directory(client_t *current);
char *parse_path(char *request, int opt);
void construct_pwd(client_t *current);
int get_command_id(char *request);
void listing(client_t *client);
void interpret_file_actions(client_t *current, int command);
void interpret_directories(client_t *current, int command);
void interpret_others(client_t *current, int command);
void interpret_authentification(client_t *crt, int cmd);

#endif /* !SERVER_H_ */
