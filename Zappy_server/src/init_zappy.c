/*
** init_zappy.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Tue Jun 27 15:10:29 2017 Mewen Le Reste
** Last update Sun Jul  2 16:36:32 2017 Mewen Le Reste
*/

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "zappy.h"

static bool		bind_zappy(t_zappy *zappy)
{
  struct sockaddr_in	sin;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(zappy->options.port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((bind(zappy->socket, (struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      fprintf(stderr, "%s%d\n", BINDERROR, zappy->options.port);
      return (false);
    }
  printf("%s%d\n", BINDSUCESS, zappy->options.port);
  if ((listen(zappy->socket, MAXCONNECTION)) == -1)
    {
      fprintf(stderr, "%s%d\n", LISTENERROR, zappy->options.port);
      return (false);
    }
  printf("%s%d\n", LISTENSUCESS, zappy->options.port);
  return (true);
}

static bool		connect_zappy(t_zappy *zappy)
{
  struct protoent	*pe;

  if (!(pe = getprotobyname("TCP")))
    {
      fprintf(stderr, TCPERROR);
      return (false);
    }
  printf(TCPSUCESS);
  if ((zappy->socket = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      fprintf(stderr, SOCKETERROR);
      return (false);
    }
  printf(SOCKETSUCESS);
  if (!bind_zappy(zappy))
    return (false);
  return (true);
}

bool			init_zappy(t_zappy *zappy)
{
  if (!init_map(zappy))
    {
      free_team(zappy->options.team);
      return (false);
    }
  zappy->players = NULL;
  zappy->viewer = NULL;
  zappy->waiter = NULL;
  zappy->eggs = NULL;
  zappy->socket = -1;
  if (!connect_zappy(zappy) ||
      !(zappy->players = init_list()) ||
      !(zappy->viewer = init_list()) ||
      !(zappy->waiter = init_list()) ||
      !(zappy->eggs = init_list()))
    {
      delete_zappy(zappy);
      return (false);
    }
  return (true);
}

static void		clear_list(t_list **list)
{
  t_node		*node;
  t_client		*client;

  node = (*list)->head;
  while (node)
    {
      client = (t_client *)node->value;
      delete_client(client);
      node = node->next;
    }
  delete_list(list);
}

void			delete_zappy(t_zappy *zappy)
{
  t_node		*node;
  t_egg		*egg;

  if (zappy->socket != -1)
    close(zappy->socket);
  delete_map(zappy);
  free_team(zappy->options.team);
  if (zappy->players)
    clear_list(&zappy->players);
  if (zappy->viewer)
    clear_list(&zappy->viewer);
  if (zappy->waiter)
    clear_list(&zappy->waiter);
  if (zappy->eggs)
    {
      node = zappy->eggs->head;
      while (node)
        {
          egg = (t_egg *)node->value;
          free(egg->team);
          free(egg);
          node = node->next;
        }
      delete_list(&zappy->eggs);
    }
}
