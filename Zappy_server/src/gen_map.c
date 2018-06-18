/*
** gen_map.c for gen_map in PSU_2016_zappy/Zappy_server/src
**
** Made by AdelyanTV-VM
** Login   <thomas.bouillon@epitech.eu>
**
** Started on  Tue Jun 27 16:40:18 2017 AdelyanTV-VM
** Last update Sun Jul  2 21:25:17 2017 AdelyanTV-VM
*/

#include "zappy.h"

static void	add_ressources(t_zappy *zappy, int x, int y, int nb)
{
  if (nb > 70 || nb < 20)
    zappy->cells[y][x].food = zappy->cells[y][x].food + 3;
  if (nb < 75 && nb > 40)
    ++zappy->cells[y][x].ressources[LINEMATE];
  if (nb > 42 && nb < 50)
    ++zappy->cells[y][x].ressources[SIBUR];
  if (nb > 65 && nb < 75)
    ++zappy->cells[y][x].ressources[DERAUMERE];
  if (nb > 50 && nb < 85)
    ++zappy->cells[y][x].ressources[MENDIANE];
  if (nb < 30 && nb > 10)
    ++zappy->cells[y][x].ressources[PHIRAS];
  if (nb == 97 || nb == 42 || nb == 84 || nb < 7)
    ++zappy->cells[y][x].ressources[THYSTAME];
}

int		nb_len(unsigned int nb)
{
  int		n;

  n = 1;
  while (nb >= 10)
    {
      ++n;
      nb /= 10;
    }
  return (n);
}

bool		send_bct(t_zappy *zappy, unsigned int x,
			 unsigned int y, bool all)
{
  bool		ret;
  int		n;
  char		*msg;
  unsigned int	size;

  n = 0;
  size = 13 + nb_len(x) + nb_len(y) + nb_len(zappy->cells[y][x].food);
  while (n != NBRESSOURCE)
    {
      size += nb_len(zappy->cells[y][x].ressources[n]);
      ++n;
    }
  if (!(msg = malloc(size)))
    return (false);
  sprintf(msg, BCTMSG, x, y, CURRCELLF, CURRCELLR[0], CURRCELLR[1],
	  CURRCELLR[2], CURRCELLR[3], CURRCELLR[4], CURRCELLR[5]);
  if (all)
    ret = send_to_viewer(zappy, msg);
  else
    ret = send_to(zappy->current, msg);
  free(msg);
  return (ret);
}

bool		generate_map(t_zappy *zappy, bool add, bool msg, bool all)
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  x = 0;
  while (y != zappy->options.height)
    {
      x = 0;
      while (x != zappy->options.width)
	{
	  if (zappy->cells[y][x].food == 0)
	    zappy->cells[y][x].food = 3;
	  if (add)
	    add_ressources(zappy, x, y, rand() % 100);
	  if (msg && !send_bct(zappy, x, y, all))
	    return (false);
	  ++x;
	}
      ++y;
    }
  return (true);
}
