/*
** content_map.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Tue Jun 27 16:55:03 2017 Dante Grossi
** Last update Thu Jun 29 19:33:09 2017 Mewen Le Reste
*/

#include "viewer.h"

bool	content_map(t_zappy *zappy, __attribute__((unused))const char **request)
{
  bool	ret;

  ret = generate_map(zappy, false, true, false);
  return (ret);
}
