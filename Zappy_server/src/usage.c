/*
** usage.c for zappy in /home/lerest_m/Desktop/Programmation/C/PSU/PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Sun Jul  2 22:51:48 2017 Mewen Le Reste
** Last update Sun Jul  2 22:52:23 2017 Mewen Le Reste
*/

#include "zappy.h"

void	usage(const char *name)
{
  fprintf(stderr, "USAGE: %s%s%s", name, USAGE1, USAGE2);
  fprintf(stderr, "%s", USAGEPORT);
  fprintf(stderr, "%s", USAGEWIDTH);
  fprintf(stderr, "%s", USAGEHEIGHT);
  fprintf(stderr, "%s", USAGENAME);
  fprintf(stderr, "%s%s", USAGECLIENT1, USAGECLIENT2);
  fprintf(stderr, "%s%s", USAGEFREQ1, USAGEFREQ2);
}
