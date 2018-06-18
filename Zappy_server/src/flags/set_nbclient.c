/*
** set_nbclient.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/flags/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 16:10:24 2017 Mewen Le Reste
** Last update Tue Jun 27 13:35:37 2017 Mewen Le Reste
*/

#include "flags.h"

int	set_nbclient(const char **av, int ac, int *i, t_options *op)
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
      op->nb_client = atoi(av[n]);
      return (0);
    }
  else
    {
      fprintf(stderr, "%s to -c\n", NOPARAM);
      fprintf(stderr, SEEUSAGE);
    }
  return (-1);
}
