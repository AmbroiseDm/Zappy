/*
** win.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Sun Jul  2 23:10:43 2017 Mewen Le Reste
** Last update Sun Jul  2 23:14:02 2017 Mewen Le Reste
*/

#include "zappy.h"

void	win(t_zappy *zappy)
{
  char	*msg;

  if (!(msg = malloc(strlen(zappy->current->team) + 4)))
    return ;
  if (sprintf(msg, "seg %s", zappy->current->team) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return ;
    }
  free(msg);
}
