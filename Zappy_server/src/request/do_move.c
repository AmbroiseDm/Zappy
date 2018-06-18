/*
** do_move.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 10:03:25 2017 Dante Grossi
** Last update Mon Jul  3 00:03:27 2017 Mewen Le Reste
*/

#include "request.h"

bool	send_ppo(t_zappy *zappy, const t_client *client)
{
  bool	ret;
  char	*msg;
  int			angle;

  angle = ((client->angle / 90) + 1);
  if (angle == 1)
    angle = 3;
  else if (angle == 3)
    angle = 1;
  if (angle == 2)
    angle = 4;
  else if (angle == 4)
    angle = 2;
  if (!(msg = malloc(nb_len(client->cell->x) +
		     nb_len(client->cell->y) +
		     nb_len(angle) +
		     nb_len(client->fd) + 8)))
    return (false);
  sprintf(msg, "ppo %d %d %d %d", client->fd, client->cell->x,
	  client->cell->y, angle);
  ret = send_to_viewer(zappy, msg);
  free(msg);
  return (ret);
}

bool	do_forward(t_zappy *zappy, __attribute__((unused))const char **request)
{
  --zappy->current->cell->nb_player;
  if (zappy->current->angle == UP)
    zappy->current->cell = zappy->current->cell->up;
  else if (zappy->current->angle == LEFT)
    zappy->current->cell = zappy->current->cell->left;
  else if (zappy->current->angle == DOWN)
    zappy->current->cell = zappy->current->cell->down;
  else if (zappy->current->angle == RIGHT)
    zappy->current->cell = zappy->current->cell->right;
  ++zappy->current->cell->nb_player;
  if (!send_to(zappy->current, OKPLAYER) ||
      !sort_cmd(zappy) ||
      !send_ppo(zappy, zappy->current))
    return (false);
  return (true);
}

bool	do_right(t_zappy *zappy, __attribute__((unused))const char **request)
{
  zappy->current->angle -= 90;
  if (zappy->current->angle < 0)
    zappy->current->angle = 270;
  if (!send_to(zappy->current, OKPLAYER) ||
      !sort_cmd(zappy) ||
      !send_ppo(zappy, zappy->current))
    return (false);
  return (true);
}

bool	do_left(t_zappy *zappy, __attribute__((unused))const char **request)
{
  zappy->current->angle += 90;
  if (zappy->current->angle > 270)
    zappy->current->angle = 0;
  if (!send_to(zappy->current, OKPLAYER) ||
      !sort_cmd(zappy) ||
      !send_ppo(zappy, zappy->current))
    return (false);
  return (true);
}
