/*
** team_names.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 16:56:02 2017 Dante Grossi
** Last update Fri Jun 30 20:17:28 2017 Mewen Le Reste
*/

#include "viewer.h"

bool	team_names(t_zappy *zappy, __attribute__((unused))const char **request)
{
  bool	ret;
  int	y;
  char	*msg;

  y = 0;
  while (zappy->options.team[y].name)
    {
      if (!(msg = malloc(strlen(zappy->options.team[y].name) + 5)))
	return (false);
      sprintf(msg, "tna %s", zappy->options.team[y].name);
      ret = send_to(zappy->current, msg);
      free(msg);
      if (!ret)
	return (false);
      ++y;
    }
  return (true);
}
