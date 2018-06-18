/*
** select_zappy.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Tue Jun 27 19:58:31 2017 Mewen Le Reste
** Last update Fri Jun 30 20:13:44 2017 Mewen Le Reste
*/

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "zappy.h"

static void		write_to(t_list **list, int fd)
{
  bool			ret;
  t_node		*node;
  char			*str;

  ret = true;
  node = (*list)->head;
  while (node)
    {
      str = (char *)node->value;
      dprintf(fd, "%s\n", str);
      free(str);
      node = node->next;
    }
  while (ret)
    ret = del_back(list);
}

static bool		select_client(t_zappy *zappy, t_list **list, t_type type)
{
  bool			needRead;
  t_node		*node;

  node = (*list)->head;
  zappy->current_type = type;
  while (node)
    {
      zappy->current = (t_client *)node->value;
      needRead = FD_ISSET(zappy->current->fd, &zappy->fd_read);
      if ((needRead || zappy->current->read_more) &&
	  !read_client(zappy, needRead))
	return (false);
      if (zappy->current && FD_ISSET(zappy->current->fd, &zappy->fd_write))
	write_to(&zappy->current->message, zappy->current->fd);
      if (zappy->current)
	node = node->next;
      else
	node = (*list)->head;
    }
  return (true);
}

static bool		add_client(t_zappy *zappy)
{
  int			fd;
  unsigned int		len;
  struct sockaddr_in	csin;

  len = sizeof(csin);
  if ((fd = accept(zappy->socket, (struct sockaddr *)&csin, &len)) == -1 ||
      !init_client(zappy, fd, "", WAITER))
    return (false);
  printf("%s%d\n", CONNECTCLIENT, fd);
  return (true);
}

bool			select_zappy(t_zappy *zappy)
{
  if ((FD_ISSET(zappy->socket, &zappy->fd_read) && !add_client(zappy)) ||
      !select_client(zappy, &zappy->players, PLAYER) ||
      !select_client(zappy, &zappy->viewer, VIEWER) ||
      !select_client(zappy, &zappy->waiter, WAITER))
    return (false);
  return (true);
}
