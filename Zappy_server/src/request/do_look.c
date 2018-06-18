/*
** do_look.c for do_look in /home/theogalh/projet/PSU_2016_zappy/Zappy_server/src
**
** Made by AdelyanTV-VM
** Login   <thomas.bouillon@epitech.eu>
**
** Started on  Fri Jun 30 15:01:36 2017 AdelyanTV-VM
** Last update Sun Jul  2 17:22:02 2017 AdelyanTV-VM
*/

#include "request.h"

static char	*look_right(t_zappy *zappy, unsigned int j,
			    unsigned int i, char *rep)
{
  t_cell	*next;
  t_cell	*orig;

  orig = zappy->current->cell->right;
  orig = orig->up;
  if ((rep = send_cell(zappy, rep, zappy->current->cell, i)) == NULL)
    return (NULL);
  while (j != zappy->current->level + 1)
    {
      i = 0;
      next = orig;
      while (i != j * 3)
	{
	  if ((rep = send_cell(zappy, rep, next, i)) == NULL)
	    return (NULL);
	  i = i + 1;
	  next = next->down;
	}
      orig = orig->right;
      orig = orig->up;
      j = j + 1;
    }
  return (rep);
}

static char	*look_left(t_zappy *zappy, unsigned int j,
			   unsigned int i, char *rep)
{
  t_cell	*next;
  t_cell	*orig;

  orig = zappy->current->cell->left;
  orig = orig->down;
  if ((rep = send_cell(zappy, rep, zappy->current->cell, i)) == NULL)
    return (NULL);
  while (j != zappy->current->level + 1)
    {
      i = 0;
      next = orig;
      while (i != j * 3)
	{
	  if ((rep = send_cell(zappy, rep, next, i)) == NULL)
	    return (NULL);
	  i = i + 1;
	  next = next->up;
	}
      orig = orig->left;
      orig = orig->down;
      j = j + 1;
    }
  return (rep);
}

static char	*look_down(t_zappy *zappy, unsigned int j,
			   unsigned int i, char *rep)
{
  t_cell	*next;
  t_cell	*orig;

  orig = zappy->current->cell->down;
  orig = orig->right;
  if ((rep = send_cell(zappy, rep, zappy->current->cell, 0)) == NULL)
    return (NULL);
  while (j != zappy->current->level + 1)
    {
      i = 0;
      next = orig;
      while (i != j * 3)
	{
	  if ((rep = send_cell(zappy, rep, next, i)) == NULL)
	    return (NULL);
	  i = i + 1;
	  next = next->left;
	}
      orig = orig->down;
      orig = orig->right;
      j = j + 1;
    }
  return (rep);
}

static char	*look_up(t_zappy *zappy, unsigned int j,
			 unsigned int i, char *rep)
{
  t_cell	*next;
  t_cell	*orig;

  orig = zappy->current->cell->up;
  orig = orig->left;
  if ((rep = send_cell(zappy, rep, zappy->current->cell, 0)) == NULL)
    return (NULL);
  while (j != zappy->current->level + 1)
    {
      i = 0;
      next = orig;
      while (i != j * 3)
	{
	  if ((rep = send_cell(zappy, rep, next, i)) == NULL)
	    return (NULL);
	  i = i + 1;
	  next = next->right;
	}
      orig = orig->up;
      orig = orig->left;
      j = j + 1;
    }
  return (rep);
}

bool	do_look(t_zappy *zappy,
		       __attribute__((unused))const char **request)
{
  char	*rep;

  if (zappy->current->angle == UP &&
      (rep = look_up(zappy, 1, 0, NULL)) == NULL)
    return (false);
  else if (zappy->current->angle == DOWN &&
	   (rep = look_down(zappy, 1, 0, NULL)) == NULL)
    return (false);
  else if (zappy->current->angle == LEFT &&
	   (rep = look_left(zappy, 1, 0, NULL)) == NULL)
    return (false);
  else if (zappy->current->angle == RIGHT &&
	   (rep = look_right(zappy, 1, 0, NULL)) == NULL)
    return (false);
  if (!send_to(zappy->current, rep) ||
      !sort_cmd(zappy))
    return (false);
  free(rep);
  return (true);
}
