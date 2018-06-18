/*
** request.h for zappy in PSU_2016_zappy/Zappy_server/include/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 15:27:25 2017 Mewen Le Reste
** Last update Sun Jul  2 22:26:40 2017 Mewen Le Reste
*/

#ifndef REQUEST_H_
# define REQUEST_H_

# include "zappy.h"

# define NBCOMMAND	13
# define NBTILE		8
# define FOOD		"food"
# define SLINEMATE	"linemate"
# define SDERAUMERE	"deraumere"
# define SSIBUR		"sibur"
# define SMENDIANE	"mendiane"
# define SPHIRAS	"phiras"
# define STHYSTAME	"thystame"

typedef	struct		s_command
{
  char			*command;
  bool			(*fct)(t_zappy *, const char **);
  unsigned int		time_unit;
}			t_command;

bool			check_cell(t_cell *, unsigned int [7]);
bool			do_forward(t_zappy *, const char **);
bool			do_right(t_zappy *, const char **);
bool			do_left(t_zappy *, const char **);
bool			do_look(t_zappy *, const char **);
bool			do_inventory(t_zappy *, const char **);
bool			do_broadcast(t_zappy *, const char **);
bool			do_connect_nbr(t_zappy *, const char **);
bool			do_fork(t_zappy *, const char **);
bool			do_eject(t_zappy *, const char **);
bool			do_take_object(t_zappy *, const char **);
bool			do_set_object(t_zappy *, const char **);
bool			do_incantation(t_zappy *, const char **);
bool			do_unknown(t_zappy *, const char **);
int			find_tile(short [2], const t_cell *, const t_cell *);
bool			send_ppo(t_zappy *, const t_client *);
bool			send_pin(t_zappy *, const t_client *);
bool			send_pgt(t_zappy *, const t_client *, int);
bool			send_pdr(t_zappy *, const t_client *, int);
bool			send_to_cell(t_zappy *, char *, bool, int);
bool			start_incantation(t_zappy *, const char **);

#endif /* !REQUEST_H_ */
