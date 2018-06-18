/*
** player_inventory.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 17:00:45 2017 Dante Grossi
** Last update Sat Jul  1 23:06:19 2017 Mewen Le Reste
*/

#include "zappy.h"
#include "viewer.h"

static int	init_size(const t_client *client, const char *request)
{
  int	i;
  int	size;

  i = 0;
  size = 0;
  size = nb_len(client->cell->x) + nb_len(client->cell->y);
  size = size + strlen(request) + 14 + nb_len(client->food);
  while (i < NBRESSOURCE)
    {
      size = size + nb_len(client->inventory[i]);
      ++i;
    }
  return (size);
}

static char	*msg_inventory(int size, const t_client *client,
			       const char *request)
{
  char *msg;

  if ((msg = malloc(sizeof(char) * size)) == NULL)
    return (NULL);
  sprintf(msg, "pin %s %d %d %d %d %d %d %d %d %d",
	  request, client->cell->x, client->cell->y,
	  client->food, client->inventory[0],
	  client->inventory[1], client->inventory[2],
	  client->inventory[3], client->inventory[4],
	  client->inventory[5]);
  return (msg);
}

static bool	send_inventory(t_zappy *zappy, int nb,
			       const char *request)
{
  char		*msg;
  t_node	*node;
  t_client	*client;
  int		size;
  bool		ret;

  node = zappy->players->head;
  while (node)
    {
      client = (t_client *)node->value;
      if (client->fd == nb)
	{
	  size = init_size(client, request);
	  if ((msg = msg_inventory(size, client, request)) == NULL)
	    return (false);
	  ret = send_to(zappy->current, msg);
	  return (ret);
	}
      node = node->next;
    }
  return (false);
}

bool	player_inventory(t_zappy *zappy,
			 const char **request)
{
  int	nb;
  bool ret;

  if (!request[1])
    {
      ret = send_to(zappy->current, BADCMDVIEWER);
      return (ret);
    }
  if (!is_num(request[1]))
    {
      ret = send_to(zappy->current, BADCMDVIEWER);
      return (ret);
    }
  nb = atoi(request[1]);
  ret = send_inventory(zappy, nb, request[1]);
  return (ret);
}
