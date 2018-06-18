/*
** viewer.h for viewer.h in PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 16:17:27 2017 Dante Grossi
** Last update Sat Jul  1 20:19:41 2017 Mewen Le Reste
*/

#ifndef VIEWER_H
# define VIEWER_H

# include "zappy.h"

# define NBCOMMANDV	9

typedef	struct	s_vcmd
{
  char		*command;
  bool		(*fct)(t_zappy *, const char **);
}		t_vcmd;

typedef	struct	s_util
{
  char	*msg;
  t_node *node;
  t_client *client;
  int	nb;
  bool	ret;
  int	size;
}		t_util;

bool		size_map(t_zappy *, const char **);
bool		content_cell(t_zappy *, const char **);
bool		content_map(t_zappy *, const char **);
bool		team_names(t_zappy *, const char **);
bool		player_position(t_zappy *, const char **);
bool		player_lvl(t_zappy *, const char **);
bool		player_inventory(t_zappy *, const char **);
bool		get_time(t_zappy *, const char **);
bool		set_time(t_zappy *, const char **);
int		my_getnbr(const char *);

#endif /* !VIEWER */
