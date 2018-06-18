/*
** set_time.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 17:02:23 2017 Dante Grossi
** Last update Fri Jun 30 21:15:33 2017 Mewen Le Reste
*/

#include "viewer.h"

bool	set_time(t_zappy *zappy, const char **request)
{
  bool	ret;
  char	*msg;

  if (!request[1])
    {
      ret = send_to(zappy->current, BADCMDVIEWER);
      return (ret);
    }
  zappy->options.frequence = atoi(request[1]);
  if (!(msg = malloc(nb_len(zappy->options.frequence) + 5)))
    return (false);
  sprintf(msg, "sgt %d", zappy->options.frequence);
  ret = send_to(zappy->current, msg);
  free(msg);
  return (ret);
}
