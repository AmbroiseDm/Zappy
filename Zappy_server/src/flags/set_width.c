/*
** set_width.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 13:58:09 2017 Dante Grossi
** Last update Tue Jun 27 12:34:33 2017 Mewen Le Reste
*/

#include "flags.h"

static bool	check_width(t_options *op)
{
  if (op->width < 10 || op->width > 1000)
    {
      fprintf(stderr, WIDTHERROR);
      return (false);
    }
  return (true);
}

int		set_width(const char **av, int ac, int *i, t_options *op)
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
      op->width = atoi(av[n]);
      if (!check_width(op))
	return (-1);
      return (0);
    }
  else
    {
      fprintf(stderr, "%s to -x\n", NOPARAM);
      fprintf(stderr, SEEUSAGE);
    }
  return (-1);
}
