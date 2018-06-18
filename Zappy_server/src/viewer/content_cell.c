/*
** content_cell.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 16:54:14 2017 Dante Grossi
** Last update Fri Jun 30 21:15:11 2017 Mewen Le Reste
*/

#include "viewer.h"

bool		content_cell(t_zappy *zappy, const char **request)
{
  bool		ret;
  unsigned int	x;
  unsigned int	y;

  if (!request[1] || !request[2])
    {
      ret = send_to(zappy->current, BADCMDVIEWER);
      return (ret);
    }
  if (!is_num(request[1]) || !is_num(request[2]))
    {
      ret = send_to(zappy->current, BADPARAMSVIEWER);
      return (ret);
    }
  x = atoi(request[1]);
  y = atoi(request[2]);
  ret = send_bct(zappy, y, x, false);
  return (ret);
}
