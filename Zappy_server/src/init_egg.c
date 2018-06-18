/*
** init_egg.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Sat Jul  1 14:08:00 2017 Mewen Le Reste
** Last update Sun Jul  2 11:36:13 2017 Mewen Le Reste
*/

#include "zappy.h"

bool		hatch_egg(t_zappy *zappy, t_egg *egg)
{
  char		*msg;

  if (is_over(&egg->hatching))
    {
      if (!(msg = malloc(nb_len(egg->idx) + 5)))
	return (false);
      if (sprintf(msg, "eht %d", egg->idx) <= 0 ||
          !send_to_viewer(zappy, msg))
        {
          free(msg);
          return (false);
        }
      free(msg);
      egg->hatch = true;
      start(zappy, &egg->alive, 126);
    }
  return (true);
}

void		remove_egg(t_zappy *zappy, int idx)
{
  unsigned int	n;
  t_node	*node;
  t_egg	*egg;

  n = 0;
  node = zappy->eggs->head;
  while (node)
    {
      egg = (t_egg *)node->value;
      if (egg->idx == idx)
	{
    free(egg->team);
    free(egg);
	  del_at(&zappy->eggs, n);
	  return ;
	}
      node = node->next;
      ++n;
    }
}

bool		add_egg(t_zappy *zappy)
{
  t_egg	*egg;

  if (!(egg = malloc(sizeof(t_egg))))
    return (false);
  start(zappy, &egg->hatching, 600);
  egg->food = 10;
  egg->hatch = false;
  egg->by = zappy->current->fd;
  egg->idx = zappy->eggs->size + 1;
  egg->cell = zappy->current->cell;
  if (!(egg->team = strdup(zappy->current->team)) ||
      !add_back(&zappy->eggs, egg) ||
      !send_egg_to_viewer(zappy, egg))
    {
      free(egg->team);
      free(egg);
      return (false);
    }
  return (true);
}

static int	link_egg_client(t_zappy *zappy, t_egg *egg, int n)
{
  char		*msg;

  zappy->current->food = egg->food;
  zappy->current->cell = egg->cell;
  zappy->current->from_egg = true;
  if (!(msg = malloc(nb_len(egg->idx) + 5)))
    return (-1);
  if (sprintf(msg, "ebo %d", egg->idx) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (-1);
    }
  free(msg);
  remove_egg(zappy, egg->idx);
  --zappy->options.team[n].nb_client;
  return (0);
}

int		connect_egg(t_zappy *zappy, int n)
{
  int		ret;
  t_node	*node;
  t_egg		*egg;

  node = zappy->eggs->head;
  while (node)
    {
      egg = (t_egg *)node->value;
      if (_strcmp(zappy->current->team, egg->team) && egg->hatch)
	{
	  ret = link_egg_client(zappy, egg, n);
	  return (ret);
	}
      node = node->next;
    }
  return (1);
}
