/*
** tile.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/request/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Sat Jul  1 21:35:49 2017 Mewen Le Reste
** Last update Sun Jul  2 18:00:51 2017 Mewen Le Reste
*/

#include <math.h>
#include "request.h"

static short	tiles[NBTILE][2] =
  {
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1}
  };

static double	get_norm(const t_cell *from, const t_cell *to, int tile)
{
  double	ret;

  ret = pow((from->x - (to->x + tiles[tile - 1][0])), 2);
  ret += pow((from->y - (to->y + tiles[tile - 1][1])), 2);
  ret = sqrt(ret);
  return (ret);
}

static int	find_tile_from(const t_cell *from, const t_cell *to, int tile)
{
  int		ret_tile;
  int		cmp_tile;
  double	ret_norm;
  double	cmp_norm;

  ret_tile = tile;
  ret_norm = get_norm(from, to, ret_tile);
  cmp_tile = tile + 1;
  if (cmp_tile > 8)
    cmp_tile = 1;
  cmp_norm = get_norm(from, to, cmp_tile);
  if (cmp_norm < ret_norm)
    {
      ret_tile = cmp_tile;
      ret_norm = cmp_norm;
    }
  cmp_tile = tile - 1;
  if (cmp_tile <= 0)
    cmp_tile = 8;
  cmp_norm = get_norm(from, to, cmp_tile);
  if (cmp_norm < ret_norm)
    ret_tile = cmp_tile;
  return (ret_tile);
}

int		find_tile(short start_tile[2], const t_cell *from, const t_cell *to)
{
  int		tile;
  int		ret;

  tile = 0;
  while (tile != NBTILE)
    {
      if (tiles[tile][0] == start_tile[0] && tiles[tile][1] == start_tile[1])
	{
	  if (tile == 8)
	    ret = find_tile_from(from, to, 1);
	  else
	    ret = find_tile_from(from, to, (tile + 1));
	  return (ret);
	}
      ++tile;
    }
  return (0);
}
