/*
** viewer.c for zappy in PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 16:15:29 2017 Dante Grossi
** Last update Fri Jun 30 20:22:54 2017 Mewen Le Reste
*/

#include "viewer.h"

static t_vcmd	vcom[NBCOMMANDV] =
  {
    {"msz", &size_map},
    {"bct", &content_cell},
    {"mct", &content_map},
    {"tna", &team_names},
    {"ppo", &player_position},
    {"plv", &player_lvl},
    {"pin", &player_inventory},
    {"sgt", &get_time},
    {"sst", &set_time}
  };

static bool	call_command_viewer(t_zappy *zappy, const char **request)
{
  bool		ret;
  int		i;

  i = 0;
  while (i != NBCOMMANDV)
    {
      if (_strcmp(request[0], vcom[i].command))
	{
	  ret = vcom[i].fct(zappy, (const char **)request);
	  return (ret);
	}
      ++i;
    }
  if (!send_to(zappy->current, BADCMDVIEWER))
    return (false);
  return (true);
}

bool		find_command_viewer(t_zappy *zappy, const char *str)
{
  bool		ret;
  char		*cmd;
  char		**request;

  if (!(cmd = trim(str)) ||
      !(request = split(cmd, ' ')))
    {
      free(cmd);
      return (false);
    }
  free(cmd);
  ret = call_command_viewer(zappy, (const char **)request);
  free_double(request);
  return (ret);
}
