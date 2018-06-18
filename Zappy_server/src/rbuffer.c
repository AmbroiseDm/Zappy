/*
** rbuffer.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:13:35 2017 Mewen Le Reste
** Last update Mon Jun 26 12:13:38 2017 Mewen Le Reste
*/

#include "rbuffer.h"

void		rfree(t_rbuffer *buffer)
{
  if (buffer)
    {
      if (buffer->buffer)
	free(buffer->buffer);
      free(buffer);
    }
}

bool		rincrease(t_rbuffer *buffer)
{
  buffer->index = (buffer->index + 1) % buffer->size;
  if (buffer->index == buffer->end)
    return (false);
  return (true);
}

t_rbuffer	*rmalloc(uint16_t size)
{
  t_rbuffer	*buffer;

  if (!(buffer = malloc(sizeof(t_rbuffer))))
    return (NULL);
  buffer->end = 0;
  buffer->index = 0;
  buffer->size = size;
  if (!(buffer->buffer = calloc(size, size)))
    {
      free(buffer);
      return (NULL);
    }
  return (buffer);
}

int		rread(int fd, t_rbuffer *buffer)
{
  int		ret;
  int		size;
  int		n;
  char		*sbuffer;

  n = 0;
  size = buffer->end - buffer->index;
  if (size <= 0)
    size += buffer->size + 1;
  if (!(sbuffer = calloc(size, size)))
    return (-1);
  if ((ret = read(fd, sbuffer, (size - 1))) > 0)
    {
      while (sbuffer[n])
	{
	  buffer->buffer[buffer->end] = sbuffer[n++];
	  buffer->end = (buffer->end + 1) % buffer->size;
	}
    }
  free(sbuffer);
  return (ret);
}
