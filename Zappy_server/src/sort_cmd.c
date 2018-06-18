/*
** sort_cmd.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Sat Jul  1 18:39:16 2017 Mewen Le Reste
** Last update Sat Jul  1 20:08:26 2017 Mewen Le Reste
*/

#include "zappy.h"

bool	sort_cmd(t_zappy *zappy)
{
  int		n;

  n = 0;
  while (zappy->current->command[n])
    {
      free(zappy->current->command[n]);
      zappy->current->command[n] = NULL;
      if (zappy->current->command[n + 1])
	{
    if (!(zappy->current->command[n] = strdup(zappy->current->command[n + 1])))
	    return (false);
	  ++n;
	}
      else
	return (true);
    }
  return (true);
}
