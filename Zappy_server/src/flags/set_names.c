/*
** set_names.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 14:08:32 2017 Dante Grossi
** Last update Fri Jun 30 20:00:51 2017 Mewen Le Reste
*/

#include "flags.h"

static bool	is_already_use(t_options *op, const char *name, int pos)
{
  int		n;

  n = 0;
  if (_strcmp(GRAPHICTEAM, name))
    {
      fprintf(stderr, "Error: %s cannot be used as a team name\n", name);
      op->team[pos].name = NULL;
      return (true);
    }
  while (n != pos)
    {
      if (_strcmp(op->team[n].name, name))
	{
	  fprintf(stderr, "Error: %s is already use\n", name);
	  op->team[pos].name = NULL;
	  return (true);
	}
      ++n;
    }
  return (false);
}

static bool	set_from_to(const char **av, int from, int to, t_options *op)
{
  int		n;

  if (op->team)
    free_team(op->team);
  if (!(op->team = malloc(sizeof(t_team) * ((to - from) + 2))))
    return (false);
  n = 0;
  while (from <= to)
    {
      if (is_already_use(op, av[from], n) ||
	  !(op->team[n].name = strdup(av[from])))
	{
	  free_team(op->team);
	  op->team = NULL;
	  return (false);
	}
      op->team[n].nb_client = 0;
      ++from;
      ++n;
    }
  op->team[n].name = NULL;
  return (true);
}

int		set_names(const char **av, int ac, int *i, t_options *op)
{
  int		n;
  int		ret;

  ret = *i;
  n = ret + 1;
  while (n != ac && av[n][0] != '-')
    ++n;
  --n;
  if (n == ret)
    {
      fprintf(stderr, "%s to -n\n", NOPARAM);
      fprintf(stderr, SEEUSAGE);
      return (-1);
    }
  if (!set_from_to(av, (ret + 1), n, op))
    return (-1);
  *i = n;
  return (0);
}
