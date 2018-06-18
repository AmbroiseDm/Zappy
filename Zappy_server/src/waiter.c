/*
** waiter.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Fri Jun 30 16:50:16 2017 Mewen Le Reste
** Last update Sun Jul  2 22:58:55 2017 Mewen Le Reste
*/

#include "viewer.h"

static bool	send_graphic_greetings(t_zappy *zappy)
{
  t_node		*node;
  t_client	*client;
  t_egg		*egg;

  if (!generate_map(zappy, false, true, false) ||
      !team_names(zappy, NULL))
    return (false);
  node = zappy->players->head;
  while (node)
    {
      client = (t_client *)node->value;
      if (!send_client_to_viewer(zappy, client))
	return (false);
      node = node ->next;
    }
  node = zappy->eggs->head;
  while (node)
    {
      egg = (t_egg *)node->value;
      if (!send_egg_to_viewer(zappy, egg))
	return (false);
      node = node ->next;
    }
  return (true);
}

static int	switch_graphic(t_zappy *zappy)
{
  char		*msg;

  if (!switch_list(zappy, zappy->current->fd, VIEWER) ||
      !(msg = malloc(nb_len(MAPWIDTH) + nb_len(MAPHEIGHT) + 6)))
    return (-1);
  if (sprintf(msg, "msz %d %d", MAPWIDTH, MAPHEIGHT) <= 0 ||
      !send_to(zappy->current, msg))
    {
      free(msg);
      return (-1);
    }
  free(msg);
  if (!(msg = malloc(nb_len(zappy->options.frequence) + 5)))
    return (-1);
  if (sprintf(msg, "sgt %d", zappy->options.frequence) <= 0 ||
      !send_to(zappy->current, msg))
    {
      free(msg);
      return (-1);
    }
  free(msg);
  if (!send_graphic_greetings(zappy))
    return (-1);
  return (1);
}

static bool	send_player_greetings(t_zappy *zappy, int n)
{
  char		*msg;
  int		client_num;

  client_num = zappy->options.nb_client - zappy->options.team[n].nb_client;
  if (!(msg = malloc(nb_len(client_num) + 1)))
    return (false);
  if (sprintf(msg, "%d", client_num) <= 0 ||
      !send_to(zappy->current, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  if (!(msg = malloc(nb_len(MAPWIDTH) + nb_len(MAPHEIGHT) + 3)))
    return (false);
  if (sprintf(msg, " %d %d", MAPWIDTH, MAPHEIGHT) <= 0 ||
      !send_to(zappy->current, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

static int	switch_player(t_zappy *zappy, const char *str)
{
  int		n;

  n = 0;
  while (zappy->options.team[n].name)
    {
      if (_strcmp(zappy->options.team[n].name, str))
        {
	  if (connect_egg(zappy, n) == 0 ||
	      zappy->options.team[n].nb_client < zappy->options.nb_client)
	    {
	      ++zappy->options.team[n].nb_client;
	      if (!switch_list(zappy, zappy->current->fd, PLAYER) ||
		  !send_player_greetings(zappy, n) ||
		  !send_client_to_viewer(zappy, zappy->current))
		return (-1);
	      return (1);
	    }
        }
      ++n;
    }
  if (!send_to(zappy->current, KOPLAYER))
    return (-1);
  return (0);
}

bool		find_command_waiter(t_zappy *zappy, const char *str)
{
  int		ret;

  if (zappy->current->team)
    free(zappy->current->team);
  if (!(zappy->current->team = strdup(str)))
    return (false);
  if (_strcmp(GRAPHICTEAM, str))
    ret = switch_graphic(zappy);
  else
    ret = switch_player(zappy, str);
  free(zappy->current->buffer);
  zappy->current->buffer = NULL;
  if (ret != -1 && !(zappy->current->buffer = calloc(1, 1)))
    return (false);
  if (ret == 1)
    zappy->current = NULL;
  if (ret == -1)
    return (false);
  return (true);
}
