/*
** player_position.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 16:58:29 2017 Dante Grossi
** Last update Sat Jul  1 17:22:30 2017 Dante Grossi
*/

#include "viewer.h"

static bool	send_position(t_zappy *zappy, int idx)
{
  bool		ret;
  char		*msg;
  t_node		*node;
  t_client	*client;

  node = zappy->players->head;
  while (node)
    {
      client = (t_client *)node->value;
      if (client->fd == idx)
	{
	  if (!(msg = malloc(nb_len(client->cell->x) + nb_len(client->cell->y) +
			     nb_len(client->angle) + nb_len(idx) + 6)))
	    return (false);
		sprintf(msg, "ppo %d %d %d %d", idx,
			client->cell->x, client->cell->y, client->angle);
	  ret = send_to(zappy->current, msg);
	  free(msg);
	  return (ret);
	}
      node = node->next;
    }
  ret = send_to(zappy->current, BADPARAMSVIEWER);
  return (ret);
}

bool	player_position(t_zappy *zappy, const char **request)
{
  bool	ret;
  int	idx;

  if (!request[1])
    {
      ret = send_to(zappy->current, BADCMDVIEWER);
      return (ret);
    }
  if (!is_num(request[1]))
    {
      ret = send_to(zappy->current, BADPARAMSVIEWER);
      return (ret);
    }
  idx = atoi(request[1]);
  ret = send_position(zappy, idx);
  return (ret);
}
