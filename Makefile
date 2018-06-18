##
## Makefile for List in /home/lerest_m/Programmation/C/ChainedList/
##
## Made by Mewen Le Reste
## Login   <mewen.lereste@epitech.eu>
##
## Started on  Tue Apr 18 15:11:34 2017 Mewen Le Reste
## Last update Mon May 29 22:13:55 2017 Mewen Le Reste
##

SERVER = ./zappy_server

SERVPATH = ./Zappy_server/

CLIENT = ./zappy_ai

CLIPATH = ./Zappy_ai/

all: $(SERVER) $(CLIENT)

$(SERVER):
	make -C $(SERVPATH)

$(CLIENT):
	make -C $(CLIPATH)

clean:
	make -C $(SERVPATH) clean
	make -C $(CLIPATH) clean

fclean: clean
	make -C $(SERVPATH) fclean
	make -C $(CLIPATH) fclean

re: fclean all

.PHONY: all clean fclean re
