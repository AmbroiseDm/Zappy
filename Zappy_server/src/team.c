/*
** team.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Fri Jun 30 19:55:31 2017 Mewen Le Reste
** Last update Fri Jun 30 19:57:11 2017 Mewen Le Reste
*/

#include "zappy.h"

void	free_team(t_team *team)
{
  int	n;

  n = 0;
  if (!team)
    return ;
  while (team[n].name)
    {
      free(team[n].name);
      ++n;
    }
  free(team);
}
