/*
** trim.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:45:43 2017 Mewen Le Reste
** Last update Mon Jun 26 12:45:49 2017 Mewen Le Reste
*/

#include "zappy.h"

bool		_strcmp(const char *str1, const char *str2)
{
  if (!str1 && !str2)
    return (true);
  else if (!str1 || !str2)
    return (false);
  else if (strcmp(str1, str2) == 0)
    return (true);
  return (false);
}

char		*merge_request(const char **request)
{
  int		n;
  char		*msg;

  n = 1;
  if (!request[0] ||
      (request[0][0] != ':' && !(msg = strdup(request[0]))) ||
      (request[0][0] == ':' && !(msg = strdup(&request[0][1]))))
    return (NULL);
  while (request[n])
    {
      if (!(msg = realloc(msg, strlen(msg) + strlen(request[n]) + 2)) ||
	  !(msg = strcat(msg, " ")) ||
	  !(msg = strcat(msg, request[n])))
	return (NULL);
      ++n;
    }
  return (msg);
}

static int	my_space(const char *str, int n)
{
  while (str[n] == ' ' || str[n] == '\t')
    ++n;
  return (n);
}

char		*trim(const char *str)
{
  int		n;
  char		*trim;
  char		buffer[2];

  n = my_space(str, 0);
  buffer[1] = '\0';
  if ((trim = calloc(1, 1)) == NULL)
    return (NULL);
  while (str[n] != '\0')
    {
      buffer[0] = str[n];
      if (buffer[0] == '\t')
	buffer[0] = ' ';
      n = my_space(str, n);
      if (str[n] == '\0')
	return (trim);
      if (!(trim = realloc(trim, strlen(trim) + strlen(buffer) + 1)) ||
	  !(trim = strcat(trim, buffer)))
	return (NULL);
      if (buffer[0] != ' ')
	++n;
    }
  return (trim);
}
