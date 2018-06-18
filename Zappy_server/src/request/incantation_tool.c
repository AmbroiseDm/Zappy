/*
** tool.c for tool in /home/theogalh/projet/PSU_2016_zappy/Zappy_server/src
**
** Made by AdelyanTV-VM
** Login   <thomas.bouillon@epitech.eu>
**
** Started on  Sun Jul  2 11:26:17 2017 AdelyanTV-VM
** Last update Sun Jul  2 15:07:07 2017 Mewen Le Reste
*/

#include "request.h"

bool		check_cell(t_cell *cell, unsigned int needed[7])
{
  int		i;

  i = 0;
  while (i != NBRESSOURCE)
    {
      if (cell->ressources[i] != needed[i])
	return (false);
      ++i;
    }
  if (cell->nb_player != needed[6])
    return (false);
  return (true);
}

static bool	increase_level(t_zappy *zappy, t_client *client, int lvl)
{
  char		*msg;

  if (client->level == (unsigned int)lvl)
    client->level = (lvl + 1);
  if ((msg = malloc(nb_len(zappy->current->level) + 15)) == NULL)
    return (false);
  if (sprintf(msg, "Current level %d", zappy->current->level) < 0 ||
      !send_to(client, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

static bool	up_client(t_zappy *zappy, t_client *client, int lvl)
{
  char		*msg;

  if (lvl != -1 && !increase_level(zappy, client, lvl))
    return (false);
  if (!(msg = malloc(nb_len(client->fd) + nb_len(client->level) + 6)))
    return (false);
  if (sprintf(msg, "plv %d %d", client->fd, client->level) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

bool		send_to_cell(t_zappy *zappy, char *msg, bool plv, int lvl)
{
  t_node	*node;
  t_client	*client;

  node = zappy->players->head;
  while (node)
    {
      client = (t_client *)node->value;
      if (zappy->current->cell->x == client->cell->x &&
	  zappy->current->cell->y == client->cell->y)
	{
	  if ((msg && !send_to(client, msg)) ||
	      (plv && !up_client(zappy, client, lvl)))
	    return (false);
	}
      node = node->next;
    }
  return (true);
}
