/*
** set_port.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 13:46:22 2017 Dante Grossi
** Last update Tue Jun 27 13:13:43 2017 Mewen Le Reste
*/

#include "flags.h"

int	set_port(const char **av, int ac, int *i, t_options *op)
{
  int	n;

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
      op->port = atoi(av[n]);
      return (0);
    }
  else
    {
      fprintf(stderr, "%s to -p\n", NOPARAM);
      fprintf(stderr, SEEUSAGE);
    }
  return (-1);
}
