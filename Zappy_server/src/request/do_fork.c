/*
** do_fork.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:19:02 2017 Dante Grossi
** Last update Sun Jul  2 11:33:52 2017 Mewen Le Reste
*/

#include "request.h"

bool	do_fork(t_zappy *zappy, __attribute__((unused))const char **request)
{
  char	*msg;

  if (!(msg = malloc(nb_len(zappy->current->fd) + 5)))
    return (false);
  if (sprintf(msg, "pfk %d", zappy->current->fd) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  if (!add_egg(zappy) ||
      !send_to(zappy->current, OKPLAYER) ||
      !sort_cmd(zappy))
    return (false);
  return (true);
}
