/*
** object_send.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/request/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Sun Jul  2 22:18:39 2017 Mewen Le Reste
** Last update Sun Jul  2 22:27:43 2017 Mewen Le Reste
*/

#include "request.h"

bool	send_pin(t_zappy *zappy, const t_client *client)
{
  bool		ret;
  int	i;
  int	size;
  char *msg;

  i = 0;
  size = nb_len(client->cell->x) + nb_len(client->cell->y)
      + nb_len(client->fd) + 14 + nb_len(client->food);
  while (i < NBRESSOURCE)
    {
      size = size + nb_len(client->inventory[i]);
      ++i;
    }
  if ((msg = malloc(sizeof(char) * size)) == NULL)
    return (false);
  sprintf(msg, "pin %d %d %d %d %d %d %d %d %d %d",
	  client->fd, client->cell->x, client->cell->y,
	  client->food, client->inventory[0],
	  client->inventory[1], client->inventory[2],
	  client->inventory[3], client->inventory[4],
	  client->inventory[5]);
  ret = send_to_viewer(zappy, msg);
  free(msg);
  return (ret);
}

bool	send_pgt(t_zappy *zappy, const t_client *client, int ressources)
{
  char *msg;

  if (!(msg = malloc(nb_len(client->fd) + nb_len(ressources) + 6)))
    return (false);
  if (sprintf(msg, "pgt %d %d", client->fd, ressources) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}

bool	send_pdr(t_zappy *zappy, const t_client *client, int ressources)
{
  char *msg;

  if (!(msg = malloc(nb_len(client->fd) + nb_len(ressources) + 6)))
    return (false);
  if (sprintf(msg, "pdr %d %d", client->fd, ressources) <= 0 ||
      !send_to_viewer(zappy, msg))
    {
      free(msg);
      return (false);
    }
  free(msg);
  return (true);
}
