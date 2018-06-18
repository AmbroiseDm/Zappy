/*
** do_eject.c for do_eject in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:20:03 2017 Dante Grossi
** Last update Sun Jul  2 12:57:38 2017 Mewen Le Reste
*/

#include "request.h"

static bool	send_eject(t_zappy *zappy)
{
  char		*msg;

  if ((msg = malloc(sizeof(char) * nb_len(zappy->current->fd) + 10)) == NULL)
    return (false);
  if (sprintf(msg, "pex %d", zappy->current->fd) < 0)
    return (false);
  if (!send_to_viewer(zappy, msg))
    return (false);
  free(msg);
  return (true);
}

static int	get_direction(t_client *client, t_cell *cell)
{
  if (cell == client->cell->up)
    return (1 + 2 * (client->angle / 90));
  else if (cell == client->cell->left)
    return (3 + 2 * (client->angle / 90));
  else if (cell == client->cell->down)
    return (5 + 2 * (client->angle / 90));
  else
    return (7 + 2 * (client->angle / 90));
}

static bool	eject_player(t_zappy *zappy, t_client *client, t_cell *next)
{
  int		k;
  char		*msg;

  k = get_direction(client, next);
  client->cell->nb_player = client->cell->nb_player - 1;
  client->cell = next;
  next->nb_player = next->nb_player + 1;
  if ((msg = malloc(nb_len(k) + 8)) == NULL)
    return (false);
  if (sprintf(msg, "eject: %d", k) <= 0 ||
      !send_ppo(zappy, client) ||
      !send_to(client, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

bool		do_eject(t_zappy *zappy,
			 __attribute__((unused))const char **request)
{
  t_node	*tmp;
  bool		ret;

  if ((tmp = zappy->players->head) || !send_eject(zappy))
    return (false);
  while (tmp != NULL)
    {
      if (zappy->current->cell->x == ((t_client *)tmp->value)->cell->x &&
	  zappy->current->cell->y == ((t_client *)tmp->value)->cell->y &&
	  zappy->current != tmp->value)
	{
	  if (zappy->current->angle == UP)
	    ret = eject_player(zappy, tmp->value, zappy->current->cell->up);
	  else if (zappy->current->angle == DOWN)
	    ret = eject_player(zappy, tmp->value, zappy->current->cell->down);
	  else if (zappy->current->angle == LEFT)
	    ret = eject_player(zappy, tmp->value, zappy->current->cell->left);
	  else if (zappy->current->angle == RIGHT)
	    ret = eject_player(zappy, tmp->value, zappy->current->cell->right);
	}
      tmp = tmp->next;
    }
  if (!ret && !sort_cmd(zappy))
    return (false);
  return (true);
}
