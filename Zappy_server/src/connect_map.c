/*
** connect_map.c for connect_map in /home/theogalh/projet/PSU_2016_zappy/Zappy_server/src
** 
** Made by AdelyanTV-VM
** Login   <thomas.bouillon@epitech.eu>
** 
** Started on  Thu Jun 29 18:13:23 2017 AdelyanTV-VM
** Last update Thu Jun 29 18:26:59 2017 AdelyanTV-VM
*/

#include "zappy.h"

static void	connect_cells(t_zappy *zappy, unsigned int x, unsigned int y)
{
  if (x == 0)
    zappy->cells[y][x].left = &zappy->cells[y][zappy->options.width - 1];
  else if (x == zappy->options.width - 1)
    zappy->cells[y][x].right = &zappy->cells[y][0];
  if (y == 0)
    zappy->cells[y][x].up = &zappy->cells[zappy->options.height - 1][x];
  else if (y == zappy->options.height - 1)
    zappy->cells[y][x].down = &zappy->cells[0][x];
  if (zappy->cells[y][x].left == NULL)
    zappy->cells[y][x].left = &zappy->cells[y][x - 1];
  if (zappy->cells[y][x].right == NULL)
    zappy->cells[y][x].right = &zappy->cells[y][x + 1];
  if (zappy->cells[y][x].up == NULL)
    zappy->cells[y][x].up = &zappy->cells[y - 1][x];
  if (zappy->cells[y][x].down == NULL)
    zappy->cells[y][x].down = &zappy->cells[y + 1][x];
}

void		connect_map(t_zappy *zappy)
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  while (y != zappy->options.height)
    {
      x = 0;
      while (x != zappy->options.width)
	{
	  connect_cells(zappy, x, y);
	  ++x;
	}
      ++y;
    }
}
