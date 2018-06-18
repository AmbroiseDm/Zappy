/*
** split.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:45:31 2017 Mewen Le Reste
** Last update Tue Jun 27 13:03:37 2017 Mewen Le Reste
*/

#include "zappy.h"

static char	**create_tab(int size)
{
  int		n;
  char		**tab;

  n = 0;
  if (!(tab = malloc(sizeof(char *) * (size + 1))))
    return (NULL);
  while (n != size)
    {
      if (!(tab[n] = malloc(1)))
	{
	  free_double(tab);
	  return (NULL);
	}
      tab[n][0] = '\0';
      ++n;
    }
  tab[size] = NULL;
  return (tab);
}

void		free_double(char **array)
{
  int		n;

  n = 0;
  if (!array)
    return ;
  while (array[n])
    {
      free(array[n]);
      ++n;
    }
  free(array);
}

static char	**fill_tab(char **tab, const char *str, char separator)
{
  int		n;
  int		i;
  char		buffer[2];

  n = 0;
  i = 0;
  buffer[1] = '\0';
  while (str[n])
    {
      buffer[0] = str[n];
      if (buffer[0] == separator)
	++i;
      else
	{
	  if (!(tab[i] = realloc(tab[i], strlen(tab[i]) + strlen(buffer) + 1)) ||
	      !(tab[i] = strcat(tab[i], buffer)))
	    return (NULL);
	}
      ++n;
    }
  return (tab);
}

char		**split(const char *str, char separator)
{
  int		n;
  int		i;
  char		**wordtab;

  n = 0;
  i = 1;
  while (str[n])
    {
      if (str[n] == separator)
	++i;
      ++n;
    }
  if ((wordtab = create_tab(i)))
    wordtab = fill_tab(wordtab, str, separator);
  return (wordtab);
}
