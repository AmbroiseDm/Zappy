/*
** do_incantation.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:24:14 2017 Dante Grossi
** Last update Sun Jul  2 17:29:45 2017 Mewen Le Reste
*/

#include "request.h"

static unsigned int	elevation[7][NBRESSOURCE + 1] =
  {
    {1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 2},
    {2, 0, 1, 0, 2, 0, 2},
    {1, 1, 2, 0, 1, 0, 4},
    {1, 2, 1, 3, 0, 0, 4},
    {1, 2, 3, 0, 1, 0, 6},
    {2, 2, 2, 2, 2, 1, 6}
  };

bool			start_incantation(t_zappy *zappy,
					  __attribute__((unused))const char **request)
{
  char			*tmp;

  if (!check_cell(zappy->current->cell, elevation[zappy->current->level - 1]))
    {
      if (!send_to_cell(zappy, KOPLAYER, false, -1))
	return (false);
    }
  else if (!send_to_cell(zappy, ELEVATION, false, -1))
    return (false);
  if (!(tmp = strdup(END)) ||
      !(tmp = realloc(tmp, strlen(zappy->current->command[0]) +
		      strlen(tmp) + 1)) ||
      !(tmp = strcat(tmp, zappy->current->command[0])))
    return (false);
  free(zappy->current->command[0]);
  if (!(zappy->current->command[0] = strdup(tmp)))
    {
      free(tmp);
      return (false);
    }
  free(tmp);
  return (true);
}

static bool		send_pie(t_zappy *zappy, const t_cell *cell, int result)
{
  char			*msg;

  if (!(msg = malloc(nb_len(cell->x) + nb_len(cell->y) + 8)))
    return (false);
  if (sprintf(msg, "pie %d %d %d", cell->x, cell->y, result) < 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

bool			do_incantation(t_zappy *zappy,
				       __attribute__((unused))const char **request)
{
  int			lvl;

  lvl = zappy->current->level - 1;
  if (check_cell(zappy->current->cell, elevation[lvl]))
    {
      if (!send_pie(zappy, zappy->current->cell, 0) ||
	  !send_to_cell(zappy, NULL, true, elevation[lvl][6]))
	return (false);
    }
  else
    {
      if (!send_pie(zappy, zappy->current->cell, 1) ||
	  !send_to_cell(zappy, KOPLAYER, false, elevation[lvl][6]))
	return (false);
    }
  if (!generate_map(zappy, false, true, true) || !sort_cmd(zappy))
    return (false);
  return (true);
}
