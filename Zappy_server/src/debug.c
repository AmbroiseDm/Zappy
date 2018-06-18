/*
** debug.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Tue Jun 27 17:09:48 2017 Mewen Le Reste
** Last update Tue Jun 27 17:20:32 2017 Mewen Le Reste
*/

#include "zappy.h"

static void	disp_cell(t_zappy *zappy, unsigned int x, unsigned int y)
{
  int		n;

  n = 0;
  printf("Cell[%d][%d]:\n", (y + 1), (x + 1));
  printf("\tFood: %d\n", zappy->cells[y][x].food);
  while (n != NBRESSOURCE)
    {
      printf("\tRessource on %d: %d\n", n, zappy->cells[y][x].ressources[n]);
      ++n;
    }
  printf("\tPlayers: %d\n", zappy->cells[y][x].nb_player);
}

void		debug(t_zappy *zappy)
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  printf("Map:\n");
  while (y != zappy->options.height)
    {
      x = 0;
      while (x != zappy->options.width)
	{
	  disp_cell(zappy, x, y);
	  ++x;
	}
      ++y;
    }
}
