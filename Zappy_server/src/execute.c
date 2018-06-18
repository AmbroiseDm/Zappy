/*
** execute.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Sat Jul  1 19:49:55 2017 Mewen Le Reste
** Last update Sun Jul  2 23:52:41 2017 Mewen Le Reste
*/

#include "zappy.h"

bool		send_pdi(t_zappy *zappy, const t_client *client)
{
  char		*pdi;

  if (!(pdi = malloc(nb_len(client->fd) + 5)))
    return (false);
  if (sprintf(pdi, "pdi %d", client->fd) <= 0 ||
      !send_to_viewer(zappy, pdi))
    {
      free(pdi);
      return (false);
    }
  free(pdi);
  return (true);
}

static bool	eat(t_zappy *zappy, t_client *client)
{
  if (is_over(&client->alive))
    {
      start(zappy, &client->alive, 126);
      if (client->food == 0)
	{
	  if (!(send_to(client, DEAD)))
	    return (false);
	  printf("%s%d\n", DEADCLIENT, client->fd);
	  remove_client(zappy, client->fd, PLAYER);
	  zappy->current = NULL;
	  return (true);
	}
      else
	--client->food;
    }
  return (true);
}

bool		check_player(t_zappy *zappy)
{
  t_node	*node;

  node = zappy->players->head;
  while (node)
    {
      zappy->current = (t_client *)node->value;
      if ((zappy->current->command[0] &&
	   !find_command_player(zappy, zappy->current->command[0])) ||
	  !eat(zappy, zappy->current))
	return (false);
      if (zappy->current && zappy->current->level == 8)
	{
	  win(zappy);
	  return (false);
	}
      if (zappy->current)
	node = node->next;
      else
	node = zappy->players->head;
    }
  return (true);
}

static int	eat_egg(t_zappy *zappy, t_egg *egg)
{
  char		*msg;

  if (is_over(&egg->alive))
    {
      start(zappy, &egg->alive, 126);
      if (egg->food == 0)
	{
	  if (!(msg = malloc(nb_len(egg->idx) + 5)))
	    return (-1);
	  if (sprintf(msg, "edi %d", egg->idx) <= 0 ||
	      !send_to_viewer(zappy, msg))
	    {
	      free(msg);
	      return (-1);
	    }
	  free(msg);
	  remove_egg(zappy, egg->idx);
	  return (1);
	}
      else
	--egg->food;
    }
  return (0);
}

bool		check_egg(t_zappy *zappy)
{
  int		ret;
  t_node	*node;
  t_egg		*egg;

  ret = 0;
  node = zappy->eggs->head;
  while (node)
    {
      egg = (t_egg *)node->value;
      if (!egg->hatch)
	{
	  if (!hatch_egg(zappy, egg))
	    return (false);
	}
      else if ((ret = eat_egg(zappy, egg)) == -1)
	return (false);
      else if (ret == 1)
	egg = NULL;
      if (egg)
	node = node->next;
      else
	node = zappy->eggs->head;
    }
  return (true);
}
