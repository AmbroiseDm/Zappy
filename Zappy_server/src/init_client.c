/*
** init_client.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Tue Jun 27 20:32:31 2017 Mewen Le Reste
** Last update Sun Jul  2 23:30:52 2017 Mewen Le Reste
*/

#include "zappy.h"

static char	**malloc_double(unsigned int size)
{
  unsigned int	n;
  char		**ret;

  n = 0;
  if (!(ret = malloc(sizeof(char *) * size)))
    return (NULL);
  while (n != size)
    {
      ret[n] = NULL;
      ++n;
    }
  return (ret);
}

static t_client	*create_client(int fd)
{
  int		n;
  t_client	*client;

  n = 0;
  if (!(client = malloc(sizeof(t_client))))
    return (NULL);
  client->fd = fd;
  client->treat = false;
  client->read_more = false;
  client->from_egg = false;
  client->food = 10;
  client->angle = 0;
  while (n != NBRESSOURCE)
    {
      client->inventory[n] = 0;
      ++n;
    }
  return (client);
}

static bool	add_client(t_zappy *zappy, t_client *client, t_type type)
{
  if ((type == PLAYER && add_back(&zappy->players, client)) ||
      (type == VIEWER && add_back(&zappy->viewer, client)) ||
      (type == WAITER && add_back(&zappy->waiter, client)))
    return (true);
  return (false);
}

bool		init_client(t_zappy *zappy, int fd, const char *team, t_type type)
{
  int		x;
  int		y;
  t_client	*client;

  if (!(client = create_client(fd)))
    return (false);
  start(zappy, &client->alive, 126);
  client->level = 1;
  x = rand() % zappy->options.width;
  y = rand() % zappy->options.height;
  client->cell = &zappy->cells[y][x];
  ++zappy->cells[y][x].nb_player;
  client->timer.set = false;
  if (!(client->team = strdup(team)) ||
      !(client->buffer = calloc(1, 1)) ||
      !(client->command = malloc_double(42)) ||
      !(client->message = init_list()) ||
      !(client->ring_buffer = rmalloc(READSIZE)) ||
      !(add_client(zappy, client, type)))
    {
      delete_client(client);
      return (false);
    }
  return (send_to(client, WELCOME));
}
