/*
** do_inventory.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:16:39 2017 Dante Grossi
** Last update Sat Jul  1 23:38:15 2017 Mewen Le Reste
*/

#include "request.h"

static int	get_inventory_size(t_zappy *zappy)
{
  int		size;

  size = 24;
  size += strlen(FOOD) + strlen(SLINEMATE) + strlen(SDERAUMERE);
  size += strlen(SSIBUR) + strlen(SMENDIANE) + strlen(SPHIRAS);
  size += strlen(STHYSTAME) + nb_len(zappy->current->food);
  size += nb_len(zappy->current->inventory[0]);
  size += nb_len(zappy->current->inventory[1]);
  size += nb_len(zappy->current->inventory[2]);
  size += nb_len(zappy->current->inventory[3]);
  size += nb_len(zappy->current->inventory[4]);
  size += nb_len(zappy->current->inventory[5]);
  return (size);
}

bool	do_inventory(t_zappy *zappy, __attribute__((unused))const char **request)
{
  char	*rep;

  rep = NULL;
  if (!(rep = malloc(get_inventory_size(zappy))))
    return (false);
  if (sprintf(rep, "[ %s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d ]",
	      FOOD, zappy->current->food,
	      SLINEMATE, zappy->current->inventory[0],
	      SDERAUMERE, zappy->current->inventory[1],
	      SSIBUR, zappy->current->inventory[2],
	      SMENDIANE, zappy->current->inventory[3],
	      SPHIRAS, zappy->current->inventory[4],
	      STHYSTAME, zappy->current->inventory[5]) <= 0)
    {
      free(rep);
      return (false);
    }
  if (!send_to(zappy->current, rep) ||
      !sort_cmd(zappy))
    return (false);
  free(rep);
  return (true);
}
