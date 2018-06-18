/*
** size_map.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 16:50:54 2017 Dante Grossi
** Last update Fri Jun 30 15:50:23 2017 Mewen Le Reste
*/

#include "viewer.h"

bool	size_map(t_zappy *zappy, __attribute__((unused))const char **request)
{
  bool	ret;
  char	*msg;

  if (!(msg = malloc(nb_len(zappy->current->cell->x) +
		     nb_len(zappy->current->cell->y) + 7)))
    return (false);
  sprintf(msg, "msz %d %d", zappy->current->cell->x, zappy->current->cell->y);
  ret = send_to(zappy->current, msg);
  free(msg);
  return (ret);
}
