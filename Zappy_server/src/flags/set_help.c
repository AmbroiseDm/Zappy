/*
** set_help.c for zappy in /home/Dante/rendu/System_Unix/PSU_2016_zappy/Zappy_server/src
**
** Made by Dante Grossi
** Login   <Dante@epitech.net>
**
** Started on  Mon Jun 26 14:26:38 2017 Dante Grossi
** Last update Mon Jun 26 16:45:29 2017 Mewen Le Reste
*/

#include "flags.h"

int	help(const char **av, __attribute__((unused))int ac,
	     __attribute__((unused))int *i, __attribute__((unused))t_options *op)
{
  usage(av[0]);
  return (1);
}
