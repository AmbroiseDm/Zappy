/*
** flag.c for zappy in PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 13:23:35 2017 Dante Grossi
** Last update Sun Jul  2 16:24:27 2017 Mewen Le Reste
*/

#include "flags.h"

static t_flag	flag[NBFLAG] =
  {
    {"-p", &set_port},
    {"-x", &set_width},
    {"-y", &set_height},
    {"-n", &set_names},
    {"-c", &set_nbclient},
    {"-f", &set_frequence},
    {"-d", &set_debug},
    {"-help", &help}
  };

int		set_debug(__attribute__((unused))const char **av,
			  __attribute__((unused))int ac,
			  __attribute__((unused))int *i, t_options *op)
{
  op->debug = true;
  return (0);
}

static int	execute_flag(const char **av, int ac, int *idx, t_options *op)
{
  int		ret;
  int		i;
  int		n;

  n = 0;
  i = *idx;
  while (n != NBFLAG)
    {
      if (_strcmp(av[i], flag[n].command))
	{
	  ret = flag[n].fct(av, ac, idx, op);
	  return (ret);
	}
      ++n;
    }
  fprintf(stderr, "Error: %s is not a known option\n", av[i]);
  fprintf(stderr, SEEUSAGE);
  return (-1);
}

bool		is_num(const char *str)
{
  int		n;

  n = 0;
  if (!str)
    return (false);
  while (str[n])
    {
      if (str[n] < '0' || str[n] > '9')
	return (false);
      ++n;
    }
  return (true);
}

static bool	set_default_options(t_options *op)
{
  if (!(op->team = malloc(sizeof(t_team) * 5)) ||
      !(op->team[0].name = strdup(TEAM1)) ||
      !(op->team[1].name = strdup(TEAM2)) ||
      !(op->team[2].name = strdup(TEAM3)) ||
      !(op->team[3].name = strdup(TEAM4)))
    {
      free_team(op->team);
      return (false);
    }
  op->team[0].nb_client = 0;
  op->team[1].nb_client = 0;
  op->team[2].nb_client = 0;
  op->team[3].nb_client = 0;
  op->team[4].name = NULL;
  op->frequence = 100;
  op->height = 10;
  op->nb_client = 100;
  op->port = 4242;
  op->width = 10;
  op->debug = false;
  return (true);
}

int		find_flag(const char **av, int ac, t_options *op)
{
  int		ret;
  int		i;

  i = 1;
  if (!set_default_options(op))
    return (-1);
  while (i < ac)
    {
      ret = execute_flag(av, ac, &i, op);
      if (ret != 0)
	return (ret);
      ++i;
    }
  return (0);
}
