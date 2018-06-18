/*
** find_command.c for zappy in PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:43:47 2017 Dante Grossi
** Last update Sat Jul  1 20:33:20 2017 Mewen Le Reste
*/

#include "request.h"

static t_command	com[NBCOMMAND] =
  {
    {"Forward", &do_forward, 7},
    {"Right", &do_right, 7},
    {"Left", &do_left, 7},
    {"Look", &do_look, 7},
    {"Inventory", &do_inventory, 1},
    {"Broadcast", &do_broadcast, 7},
    {"Connect_nbr", &do_connect_nbr, 0},
    {"Fork", &do_fork, 42},
    {"Eject", &do_eject, 7},
    {"Take", &do_take_object, 7},
    {"Set", &do_set_object, 7},
    {"Incantation", &start_incantation, 0},
    {ENDINCANT, &do_incantation, 300}
  };

static bool		launch_command(t_zappy *zappy, const char **request, int i)
{
  bool			ret;

  ret = true;
  if (!zappy->current->timer.set)
    {
      if (com[i].time_unit == 0)
	ret = com[i].fct(zappy, (const char **)request);
      else
	start(zappy, &zappy->current->timer, com[i].time_unit);
    }
  else if (is_over(&zappy->current->timer))
    ret = com[i].fct(zappy, (const char **)request);
  return (ret);
}

static bool		call_command_player(t_zappy *zappy, const char **request)
{
  bool			ret;
  int			i;

  i = 0;
  ret = true;
  while (i != NBCOMMAND)
    {
      if (_strcmp(request[0], com[i].command))
	{
	  ret = launch_command(zappy, request, i);
	  return (ret);
  	}
      ++i;
    }
  if (!send_to(zappy->current, KOPLAYER) ||
      !sort_cmd(zappy))
    return (false);
  return (true);
}

bool			find_command_player(t_zappy *zappy, const char *str)
{
  bool			ret;
  char			*cmd;
  char			**request;

  if (!(cmd = trim(str)) ||
      !(request = split(cmd, ' ')))
    {
      free(cmd);
      return (false);
    }
  free(cmd);
  ret = call_command_player(zappy, (const char **)request);
  free_double(request);
  return (ret);
}
