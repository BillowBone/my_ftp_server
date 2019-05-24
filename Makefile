##
## EPITECH PROJECT, 2019
## PSU - Network Programming - myftp
## File description:
## Makefile
##

SRC	=	./src/server.c	\
		./src/init_server.c	\
		./src/new_client.c	\
		./src/free_clients.c	\
		./src/read_clients.c	\
		./src/write_clients.c	\
		./src/close_clients.c	\
		./src/interpret_commands.c	\
		./src/interpret_request.c	\
		./src/verify_args.c	\
		./src/delete_client.c	\
		./src/display_help.c	\
		./src/my_strdup.c	\
		./src/get_bigger_socket.c	\
		./src/change_working_directory.c	\
		./src/parse_path.c	\
		./src/construct_pwd.c	\
		./src/get_command_id.c	\
		./src/listing.c	\
		./src/main.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS	=	-I./include/

all:	$(NAME)

$(NAME):	$(OBJ)
			gcc $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(NAME)

re:		fclean all
