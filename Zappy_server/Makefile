##
## Makefile for zappy in PSU_2016_zappy/Zappy_server/
##
## Made by Mewen Le Reste
## Login   <mewen.lereste@epitech.eu>
##
## Started on  Wed Jun 28 13:12:52 2017 Mewen Le Reste
## Last update Sun Jul  2 23:12:05 2017 Mewen Le Reste
##

SRCPATH = src

SRC =	$(SRCPATH)/main.c \
	$(SRCPATH)/flags/set_frequence.c \
	$(SRCPATH)/flags/set_height.c \
	$(SRCPATH)/flags/set_help.c \
	$(SRCPATH)/flags/set_names.c \
	$(SRCPATH)/flags/set_nbclient.c \
	$(SRCPATH)/flags/set_port.c \
	$(SRCPATH)/flags/set_width.c \
	$(SRCPATH)/request/do_broadcast.c \
	$(SRCPATH)/request/do_connect_nbr.c \
	$(SRCPATH)/request/do_eject.c \
	$(SRCPATH)/request/do_fork.c \
	$(SRCPATH)/request/do_incantation.c \
	$(SRCPATH)/request/do_inventory.c \
	$(SRCPATH)/request/do_look.c \
	$(SRCPATH)/request/do_move.c \
	$(SRCPATH)/request/do_move_object.c \
	$(SRCPATH)/request/incantation_tool.c \
	$(SRCPATH)/request/look_cell.c \
	$(SRCPATH)/request/object_send.c \
	$(SRCPATH)/request/tile.c \
	$(SRCPATH)/viewer/content_cell.c \
	$(SRCPATH)/viewer/content_map.c \
	$(SRCPATH)/viewer/get_time.c \
	$(SRCPATH)/viewer/player_inventory.c \
	$(SRCPATH)/viewer/player_lvl.c \
	$(SRCPATH)/viewer/player_position.c \
	$(SRCPATH)/viewer/set_time.c \
	$(SRCPATH)/viewer/size_map.c \
	$(SRCPATH)/viewer/team_names.c \
	$(SRCPATH)/connect_map.c \
	$(SRCPATH)/debug.c \
	$(SRCPATH)/delete_client.c \
	$(SRCPATH)/execute.c \
	$(SRCPATH)/flag.c \
	$(SRCPATH)/gen_map.c \
	$(SRCPATH)/init_client.c \
	$(SRCPATH)/init_egg.c \
	$(SRCPATH)/init_map.c \
	$(SRCPATH)/init_zappy.c \
	$(SRCPATH)/list_add.c \
	$(SRCPATH)/list_del.c \
	$(SRCPATH)/list.c \
	$(SRCPATH)/rbuffer.c \
	$(SRCPATH)/read.c \
	$(SRCPATH)/request.c \
	$(SRCPATH)/select_zappy.c \
	$(SRCPATH)/send_msg.c \
	$(SRCPATH)/sort_cmd.c \
	$(SRCPATH)/split.c \
	$(SRCPATH)/switch_list.c \
	$(SRCPATH)/team.c \
	$(SRCPATH)/time.c \
	$(SRCPATH)/trim.c \
	$(SRCPATH)/usage.c \
	$(SRCPATH)/viewer.c \
	$(SRCPATH)/waiter.c \
	$(SRCPATH)/win.c

OBJ = 	$(SRC:.c=.o)

NAME =	../zappy_server

CFLAGS += -W -Wall -Werror -Wextra -pedantic -I./include

LDFLAGS += -lm

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -Rf $(OBJ)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
