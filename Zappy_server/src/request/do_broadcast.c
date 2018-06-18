/*
** do_broadcast.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:17:20 2017 Dante Grossi
** Last update Sun Jul  2 23:33:21 2017 Mewen Le Reste
*/

#include <math.h>
#include "request.h"

static int	set_new_pos(short start_tile[2], const t_cell *from,
			    const t_cell *to, unsigned int size[2])
{
  t_cell	new_from;

  new_from.x = from->x;
  if (start_tile[0] == 1 && from->x < to->x)
    new_from.x += size[0];
  else if (start_tile[0] == -1 && from->x > to->x)
    new_from.x -= size[0];
  new_from.y = from->y;
  if (start_tile[1] == 1 && from->y < to->y)
    new_from.y -= size[1];
  else if (start_tile[1] == -1 && from->y > to->y)
    new_from.y += size[1];
  return (find_tile(start_tile, &new_from, to));
}

static int	search_tile(unsigned int width, unsigned int height,
			    const t_cell *from, const t_cell *to)
{
  unsigned int	dist;
  short		start_tile[2];
  unsigned int	size[2];

  size[0] = width;
  size[1] = height;
  if (from->x == to->x && from->y == to->y)
    return (0);
  dist = abs(from->x - to->x);
  if (from->x == to->x)
    start_tile[0] = 0;
  else if ((dist < (width / 2) && from->x < to->x) ||
	   (dist >= (width / 2) && from->x > to->x))
    start_tile[0] = -1;
  else
    start_tile[0] = 1;
  dist = abs(from->y - to->y);
  if (from->y == to->y)
    start_tile[1] = 0;
  else if ((dist <= (height / 2) && from->y > to->y) ||
	   (dist > (height / 2) && from->y < to->y))
    start_tile[1] = 1;
  else
    start_tile[1] = -1;
  return (set_new_pos(start_tile, from, to, size));
}

static bool	send_pbc(t_zappy *zappy, const char *text)
{
  char		*msg;

  if (!(msg = malloc(strlen(text) + nb_len(zappy->current->fd) + 7)))
    return (false);
  if (sprintf(msg, "pbc %d %s", zappy->current->fd, text) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

static bool	send_tile(t_zappy *zappy, t_client *client, const char *text)
{
  char		*msg;
  int		tile;

  tile = search_tile(MAPWIDTH, MAPHEIGHT, zappy->current->cell, client->cell);
  if (tile != 0)
    {
			tile -= 2 * (client->angle / 90);
			if (tile < 1)
	tile += 8;
    }
  if (!(msg = malloc(strlen(text) + 12)))
    return (false);
  if (sprintf(msg, "message %d, %s", tile, text) <= 0 ||
      !send_to(client, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

bool		do_broadcast(t_zappy *zappy, const char **request)
{
  t_node	*node;
  t_client	*client;

  if (!request[1])
    {
      if (!send_to(zappy->current, KOPLAYER))
	return (false);
      return (true);
    }
  node = zappy->players->head;
  while (node)
    {
      client = (t_client *)node->value;
      if (client->fd != zappy->current->fd &&
	  !send_tile(zappy, client, request[1]))
	return (false);
      node = node->next;
    }
  if (!send_pbc(zappy, request[1]) ||
      !send_to(zappy->current, OKPLAYER) ||
      !sort_cmd(zappy))
    return (false);
  return (true);
}
