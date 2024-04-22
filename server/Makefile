##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-tekspice-clement.monnoire
## File description:
## Makefile
##

SRC	=	src/main.c \
	src/server.c \
	src/client.c \
	src/log.c \
	src/command.c \
	src/destroy_tab.c \
	src/my_str_to_word_array.c \
	src/my_quote_to_world_array.c \
	src/send.c \
	src/users.c \
	src/get_file.c \
	src/context.c \
	src/create.c \
	src/list.c \
	src/subs.c

OBJ	=	$(SRC:.c=.o)

NAME	=	../myteams_server

CFLAGS = -g3 -Iinclude # -Wall -Wextra -Werror
LDFLAGS	+=	-L ../libs/myteams/ -lmyteams -luuid

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
