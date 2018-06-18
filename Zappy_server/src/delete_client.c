/*
** delete_client.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Tue Jun 27 20:21:31 2017 Mewen Le Reste
** Last update Sun Jul  2 17:16:32 2017 Mewen Le Reste
*/

#include "zappy.h"

void		delete_client(t_client *client)
{
  t_node	*node;
  char		*str;

  free(client->buffer);
  free(client->team);
  rfree(client->ring_buffer);
  free_double(client->command);
  if (client->message)
    {
      node = client->message->head;
      while (node)
        {
          str = (char *)node->value;
          dprintf(client->fd, "%s\n", str);
          free(str);
          node = node->next;
        }
      delete_list(&client->message);
    }
  close(client->fd);
  free(client);
}

static t_node	*get_type_head(t_zappy *zappy, t_type type)
{
  t_node	*node;

  if (type == PLAYER)
    node = zappy->players->head;
  else if (type == VIEWER)
    node = zappy->viewer->head;
  else if (type == WAITER)
    node = zappy->waiter->head;
  else
    return (NULL);
  return (node);
}

static void	del_type_list(t_zappy *zappy, t_type type, int n)
{
  if (type == PLAYER)
    del_at(&zappy->players, n);
  else if (type == VIEWER)
    del_at(&zappy->viewer, n);
  else if (type == WAITER)
    del_at(&zappy->waiter, n);
}

static void	delete_from_team(t_zappy *zappy, t_client *client)
{
  int		n;

  n = 0;
  while (zappy->options.team[n].name)
    {
      if (_strcmp(client->team, zappy->options.team[n].name))
	{
	  --zappy->options.team[n].nb_client;
	  return ;
	}
      ++n;
    }
}

void		remove_client(t_zappy *zappy, int fd, t_type type)
{
  unsigned int	n;
  t_node	*node;
  t_client	*client;

  n = 0;
  if (!(node = get_type_head(zappy, type)))
    return ;
  while (node)
    {
      client = (t_client *)node->value;
      if (client->fd == fd)
	{
	  if (type == PLAYER)
	    send_pdi(zappy, client);
	  if (!client->from_egg)
	    delete_from_team(zappy, client);
	  delete_client(client);
	  del_type_list(zappy, type, n);
	  return ;
	}
      node = node->next;
      ++n;
    }
}
