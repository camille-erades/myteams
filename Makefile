##
## EPITECH PROJECT, 2023
## B-NWP-400-LYN-4-1-myteams-camille.erades
## File description:
## Makefile
##

SERVER	=	server/
CLIENT	=	client/

all: server client

server:
	@ $(MAKE) -C $(SERVER) -s

client:
	@ $(MAKE) -C $(CLIENT) -s

clean:
	@ $(MAKE) clean -C $(SERVER) -s
	@ $(MAKE) clean -C $(CLIENT) -s

fclean:
	@ $(MAKE) fclean -C $(SERVER) -s
	@ $(MAKE) fclean -C $(CLIENT) -s

re:
	@ $(MAKE) re -C $(SERVER) -s
	@ $(MAKE) re -C $(CLIENT) -s

.PHONY: all server client clean fclean re
