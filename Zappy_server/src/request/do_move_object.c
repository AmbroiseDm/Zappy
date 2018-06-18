/*
** do_set_object.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:23:07 2017 Dante Grossi
** Last update Sun Jul  2 22:25:46 2017 Mewen Le Reste
*/

#include "request.h"

static char		ressources[NBRESSOURCE][10] =
{
  SLINEMATE,
  SDERAUMERE,
  SSIBUR,
  SMENDIANE,
  SPHIRAS,
  STHYSTAME
};

static bool	take_object(t_zappy *zappy, const char *object)
{
  int		n;

  n = 0;
  if (_strcmp(FOOD, object) && zappy->current->cell->food > 0)
    {
      zappy->current->food += zappy->current->cell->food;
      zappy->current->cell->food = 0;
      if (!send_pgt(zappy, zappy->current, 0))
	return (false);
  	  return (true);
    }
  while (n != NBRESSOURCE)
    {
      if (_strcmp(ressources[n], object) &&
	  zappy->current->cell->ressources[n] > 0)
	{
	  zappy->current->inventory[n] += zappy->current->cell->ressources[n];
	  zappy->current->cell->ressources[n] = 0;
    if (!send_pgt(zappy, zappy->current, (n + 1)))
return (false);
	  return (true);
	}
      ++n;
    }
  return (false);
}

bool		do_take_object(t_zappy *zappy, const char **request)
{
  bool		ret;

  if (!request[1])
    {
      ret = send_to(zappy->current, KOPLAYER);
      return (ret);
    }
  ret = take_object(zappy, request[1]);
  if (!sort_cmd(zappy))
    return (false);
  if (!ret)
    {
      ret = send_to(zappy->current, KOPLAYER);
      return (ret);
    }
  if (!send_pin(zappy, zappy->current) ||
      !send_bct(zappy, zappy->current->cell->x,
		zappy->current->cell->y, true) ||
      !send_to(zappy->current, OKPLAYER))
    return (false);
  return (true);
}

static bool	set_object(t_zappy *zappy, const char *object)
{
  int		n;

  n = 0;
  if (_strcmp(FOOD, object) && zappy->current->food > 0)
    {
      ++zappy->current->cell->food;
      --zappy->current->food;
      if (!send_pdr(zappy, zappy->current, 0))
	return (false);
  	  return (true);
    }
  while (n != NBRESSOURCE)
    {
      if (_strcmp(ressources[n], object) && zappy->current->inventory[n] > 0)
	{
	  ++zappy->current->cell->ressources[n];
	  --zappy->current->inventory[n];
    if (!send_pdr(zappy, zappy->current, (n + 1)))
return (false);
	  return (true);
	}
      ++n;
    }
  return (false);
}

bool		do_set_object(t_zappy *zappy, const char **request)
{
  bool		ret;

  if (!request[1])
    {
      ret = send_to(zappy->current, KOPLAYER);
      return (ret);
    }
  ret = set_object(zappy, request[1]);
  if (!sort_cmd(zappy))
    return (false);
  if (!ret)
    {
      ret = send_to(zappy->current, KOPLAYER);
      return (ret);
    }
  if (!send_pin(zappy, zappy->current) ||
      !send_bct(zappy, zappy->current->cell->x,
		zappy->current->cell->y, true) ||
      !send_to(zappy->current, OKPLAYER))
    return (false);
  return (true);
}
