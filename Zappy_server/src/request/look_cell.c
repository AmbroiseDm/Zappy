/*
** send_cell.c for send_cell in /home/theogalh/projet/PSU_2016_zappy/Zappy_server/src
**
** Made by AdelyanTV-VM
** Login   <thomas.bouillon@epitech.eu>
**
** Started on  Fri Jun 30 18:38:52 2017 AdelyanTV-VM
** Last update Sun Jul  2 23:53:50 2017 Mewen Le Reste
*/

#include "zappy.h"

static char	rsc[6][15] = {
  {" linemate\0"},
  {" deraumere\0"},
  {" sibur\0"},
  {" mendiane\0"},
  {" phiras\0"},
  {" thystame\0"},
};

static char	*add_food(char *rep, t_cell *cell)
{
  unsigned int	nb;

  nb = 0;
  while (nb != cell->food)
    {
      if ((rep = realloc(rep, strlen(" food") + strlen(rep) + 3)) == NULL)
	return (NULL);
      if ((rep = strcat(rep, " food")) == NULL)
	return (NULL);
      nb = nb + 1;
    }
  return (rep);
}

static char	*add_rsc(char *rep, t_cell *cell)
{
  unsigned int	i;
  unsigned int	nb;

  i = 0;
  while (i != 6)
    {
      nb = 0;
      while (nb != cell->ressources[i])
	{
	  if ((rep = realloc(rep, strlen(rsc[i]) + strlen(rep) + 3)) == NULL)
	    return (NULL);
	  if ((rep = strcat(rep, rsc[i])) == NULL)
	    return (NULL);
	  nb = nb + 1;
	}
      i = i + 1;
    }
  return (rep);
}

char		*send_cell(t_zappy *zappy, char *rep,
			   t_cell *cell, unsigned int j)
{
  unsigned int	i;

  i = 0;
  if (rep != NULL && ((rep = realloc(rep, strlen(rep) + 3)) == NULL ||
		      (rep = strcat(rep, ",")) == NULL))
    return (NULL);
  else if (rep == NULL && (rep = strdup("[")) == NULL)
    return (NULL);
  while (i != cell->nb_player)
    {
      if ((rep = realloc(rep, strlen(" player") + 10 + strlen(rep))) == NULL)
	return (NULL);
      if ((rep = strcat(rep, " player")) == NULL)
	return (NULL);
      i = i + 1;
    }
  if ((rep = add_food(rep, cell)) == NULL || (rep = add_rsc(rep, cell)) == NULL)
    return (NULL);
  if (j == (zappy->current->level * 3) - 1)
    if ((rep = realloc(rep, strlen(rep) + 3)) == NULL ||
	(rep = strcat(rep, " ]")) == NULL)
      return (NULL);
  return (rep);
}
