/*
** switch_list.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Wed Jun 28 12:54:10 2017 Mewen Le Reste
** Last update Sun Jul  2 13:43:48 2017 Mewen Le Reste
*/

#include "zappy.h"

static bool	switch_client(int fd, t_list **from, t_list **to, t_type new_type)
{
  unsigned int	n;
  t_node	*node;
  t_client	*client;

  n = 0;
  node = (*from)->head;
  while (node)
    {
      client = (t_client *)node->value;
      if (client->fd == fd)
	{
	  client->type = new_type;
	  if (!add_back(to, client) ||
	      !del_at(from, n))
	    return (false);
	  return (true);
	}
      node = node->next;
      ++n;
    }
  return (false);
}

bool		switch_list(t_zappy *zappy, int fd, t_type to)
{
  bool		ret;

  ret = false;
  if (to == PLAYER)
    {
      ret = switch_client(fd, &zappy->waiter, &zappy->players, to);
      if (ret && !generate_map(zappy, true, true, true))
	return (false);
      return (true);
    }
  else if (to == VIEWER)
    ret = switch_client(fd, &zappy->waiter, &zappy->viewer, to);
  return (ret);
}
