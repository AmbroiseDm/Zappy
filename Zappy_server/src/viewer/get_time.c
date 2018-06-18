/*
** get_time.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 17:01:53 2017 Dante Grossi
** Last update Fri Jun 30 16:59:16 2017 Mewen Le Reste
*/

#include "zappy.h"
#include "viewer.h"

bool	get_time(t_zappy *zappy, __attribute__((unused))const char **request)
{
  bool	ret;
  char	*msg;

  if (!(msg = malloc(nb_len(zappy->options.frequence) + 5)))
    return (false);
  sprintf(msg, "sgt %d", zappy->options.frequence);
  ret = send_to(zappy->current, msg);
  free(msg);
  return (ret);
}
