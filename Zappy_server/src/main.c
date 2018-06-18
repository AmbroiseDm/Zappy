/*
** main.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:17:22 2017 Mewen Le Reste
** Last update Sun Jul  2 23:34:22 2017 Mewen Le Reste
*/

#include <signal.h>
#include "zappy.h"

t_zappy			zappy;

void			sigint(int signo)
{
  (void)signo;
  delete_zappy(&zappy);
}

static void		prepare_client(t_zappy *zappy, t_list **list)
{
  t_node		*node;
  t_client		*client;

  node = (*list)->head;
  while (node)
    {
      client = (t_client *)node->value;
      if (client->fd > zappy->fd_max)
	zappy->fd_max = client->fd;
      FD_SET(client->fd, &zappy->fd_read);
      FD_SET(client->fd, &zappy->fd_write);
      node = node->next;
    }
}

static void		prepare_zappy(t_zappy *zappy)
{
  zappy->fd_max = zappy->socket;
  FD_ZERO(&zappy->fd_read);
  FD_ZERO(&zappy->fd_write);
  FD_SET(zappy->socket, &zappy->fd_read);
  prepare_client(zappy, &zappy->players);
  prepare_client(zappy, &zappy->viewer);
  prepare_client(zappy, &zappy->waiter);
}

static int		do_zappy(t_zappy *zappy)
{
  bool			loop;
  struct timeval	time;

  loop = true;
  time.tv_sec = 0;
  time.tv_usec = 1;
  while (loop)
    {
      if (!check_player(zappy) ||
	  !check_egg(zappy))
	loop = false;
      if (loop && !generate_map(zappy, false, false, false))
	loop = false;
      if (loop)
	prepare_zappy(zappy);
      if (loop && select(zappy->fd_max + 1, &zappy->fd_read,
			 &zappy->fd_write, NULL, &time) == -1)
	loop = false;
      if (loop && !select_zappy(zappy))
	loop = false;
    }
  return (84);
}

int			main(int ac, char **av)
{
  int			ret;

  srand(time(NULL));
  ret = find_flag((const char **)av, ac, &zappy.options);
  if (ret != 0)
    {
      free_team(zappy.options.team);
      if (ret == 1)
	return (0);
      return (84);
    }
  if (!init_zappy(&zappy))
    return (84);
  if (zappy.options.debug)
    debug(&zappy);
  ret = do_zappy(&zappy);
  delete_zappy(&zappy);
  return (ret);
}
