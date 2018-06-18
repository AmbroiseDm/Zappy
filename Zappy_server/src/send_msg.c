/*
** send_msg.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Wed Jun 28 15:53:29 2017 Mewen Le Reste
** Last update Mon Jul  3 00:03:32 2017 Mewen Le Reste
*/

#include "zappy.h"

bool		send_to(t_client *client, const char *msg)
{
  char		*dup;

  if (!(dup = strdup(msg)) ||
      !add_back(&client->message, dup))
    return (false);
  return (true);
}

bool		send_to_viewer(t_zappy *zappy, const char *msg)
{
  t_node	*node;
  t_client	*viewer;

  node = zappy->viewer->head;
  while (node)
    {
      viewer = (t_client *)node->value;
      if (!send_to(viewer, msg))
	return (false);
      node = node->next;
    }
  return (true);
}

bool		send_egg_to_viewer(t_zappy *zappy, const t_egg *egg)
{
  char		*msg;

  if (!(msg = malloc(nb_len(egg->idx) + nb_len(egg->by) +
		    nb_len(egg->cell->x) + nb_len(egg->cell->y) + 8)))
    return (false);
  if (sprintf(msg, "enw %d %d %d %d", egg->idx, egg->by,
	      egg->cell->x, egg->cell->y) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

bool		send_client_to_viewer(t_zappy *zappy, const t_client *client)
{
  char		*msg;
  int			angle;

  angle = ((client->angle / 90) + 1);
  if (angle == 1)
    angle = 3;
  else if (angle == 3)
    angle = 1;
  if (angle == 2)
    angle = 4;
  else if (angle == 4)
    angle = 2;
  if (!(msg = malloc(nb_len(client->fd) + nb_len(client->cell->x) +
		    nb_len(client->cell->y) + nb_len(angle) +
		    nb_len(client->level) + strlen(client->team) + 10)))
    return (false);
  if (sprintf(msg, "pnw %d %d %d %d %d %s", client->fd, client->cell->x,
	      client->cell->y, angle, client->level, client->team) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}
