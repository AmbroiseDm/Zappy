/*
** set_height.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 14:01:38 2017 Dante Grossi
** Last update Tue Jun 27 12:34:11 2017 Mewen Le Reste
*/

#include "flags.h"

static bool	check_height(t_options *op)
{
  if (op->height < 10 || op->height > 1000)
    {
      fprintf(stderr, HEIGHTERROR);
      return (false);
    }
  return (true);
}

int		set_height(const char **av, int ac, int *i, t_options *op)
{
  int		n;

  if (*i < (ac - 1))
    {
      ++(*i);
      n = *i;
      if (!is_num(av[n]))
	{
	  fprintf(stderr, "Error: %s is not a number\n", av[n]);
	  fprintf(stderr, SEEUSAGE);
	  return (-1);
	}
      op->height = atoi(av[n]);
      if (!check_height(op))
	return (-1);
      return (0);
    }
  else
    {
      fprintf(stderr, "%s to -y\n", NOPARAM);
      fprintf(stderr, SEEUSAGE);
    }
  return (-1);
}
