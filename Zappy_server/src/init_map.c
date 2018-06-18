/*
** init_map.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 16:57:01 2017 Mewen Le Reste
** Last update Thu Jun 29 18:25:24 2017 AdelyanTV-VM
*/

#include "zappy.h"

static bool	init_cell(t_zappy *zappy, unsigned int y, unsigned int x)
{
  int		n;

  n = 0;
  zappy->cells[y][x].x = x;
  zappy->cells[y][x].y = y;
  zappy->cells[y][x].food = 0;
  zappy->cells[y][x].nb_player = 0;
  zappy->cells[y][x].right = NULL;
  zappy->cells[y][x].left = NULL;
  zappy->cells[y][x].up = NULL;
  zappy->cells[y][x].down = NULL;
  while (n != NBRESSOURCE)
    {
      zappy->cells[y][x].ressources[n] = 0;
      ++n;
    }
  return (true);
}

static bool	init_row(t_zappy *zappy, unsigned int y)
{
  unsigned int	x;

  x = 0;
  if (!(zappy->cells[y] = malloc(sizeof(t_cell) * zappy->options.width)))
    return (false);
  while (x != zappy->options.width)
    {
      if (!init_cell(zappy, y, x))
	return (false);
      ++x;
    }
  return (true);
}

bool		init_map(t_zappy *zappy)
{
  unsigned int	y;

  y = 0;
  if (zappy->options.height == 0 || zappy->options.width == 0)
    return (false);
  if (!(zappy->cells = malloc(sizeof(t_cell *) * zappy->options.height)))
    return (false);
  while (y != zappy->options.height)
    {
      if (!init_row(zappy, y))
	{
	  delete_map(zappy);
	  return (false);
	}
      ++y;
    }
  connect_map(zappy);
  return (true);
}

void		delete_map(t_zappy *zappy)
{
  unsigned int	y;

  y = 0;
  if (!zappy && !zappy->cells)
    return ;
  while (y != zappy->options.height && zappy->cells[y])
    {
      free(zappy->cells[y]);
      ++y;
    }
  free(zappy->cells);
}
