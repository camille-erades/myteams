##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-tekspice-clement.monnoire
## File description:
## Makefile
##

SRC	=	src/main.c \
	src/my_str_to_word_array.c \
	src/my_quote_to_world_array.c \
	src/destroy_tab.c \
	src/get_input.c \
	src/help.c \
	src/command/command.c \
	src/command/subscribe.c \
	src/command/info_for_user.c \
	src/command/log.c \
	src/command/context.c \
	src/command/error.c

OBJ	=	$(SRC:.c=.o)

NAME	=	../myteams_cli

CFLAGS = -g3 -I include #-Wall -Wextra -Werror
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
