/*
** do_connect_nbr.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:18:12 2017 Dante Grossi
** Last update Sun Jul  2 13:01:16 2017 Mewen Le Reste
*/

#include "request.h"

bool	do_connect_nbr(t_zappy *zappy, __attribute__((unused))const char **request)
{
  int	i;
  int	res;
  char	*rep;

  i = 0;
  while (zappy->options.team[i].name != NULL)
    {
      if (strcmp(zappy->current->team, zappy->options.team[i].name))
	{
	  res = zappy->options.team[i].nb_client - zappy->options.nb_client;
	  if (res < 0)
	    res = 0;
	}
      ++i;
    }
  if ((rep = malloc(nb_len(res) + 1)) == NULL)
    return (false);
  if (sprintf(rep, "%d", res) <= 0 || !send_to(zappy->current, rep) ||
      !sort_cmd(zappy))
    {
      free(rep);
      return (false);
    }
  free(rep);
  return (true);
}
