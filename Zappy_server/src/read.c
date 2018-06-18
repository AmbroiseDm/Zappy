/*
** read.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Tue Jun 27 16:11:40 2017 Mewen Le Reste
** Last update Sun Jul  2 23:28:07 2017 Mewen Le Reste
*/

#include "zappy.h"

static bool	do_read_more(const t_rbuffer *buffer)
{
  uint16_t	n;

  n = buffer->index;
  while (n != buffer->end)
    {
      if (buffer->buffer[n] == '\n')
	return (true);
      n = (n + 1) % buffer->size;
    }
  return (false);
}

static bool	treat_rbuffer(t_zappy *zappy)
{
  bool		ret;
  char		buf[2];
  t_client	*client;

  ret = true;
  client = zappy->current;
  client->treat = false;
  client->read_more = false;
  buf[1] = '\0';
  while (ret)
    {
      buf[0] = client->ring_buffer->buffer[client->ring_buffer->index];
      if (!(client->buffer = realloc(client->buffer,
				     strlen(client->buffer) + 2)) ||
	  !(client->buffer = strcat(client->buffer, buf)))
	return (false);
      ret = rincrease(client->ring_buffer);
      if (buf[0] == '\n')
	ret = false;
    }
  if (buf[0] == '\n')
    client->treat = true;
  client->read_more = do_read_more(client->ring_buffer);
  return (true);
}

static bool	add_cmd(t_zappy *zappy)
{
  int		n;

  n = 0;
  while (zappy->current->command[n])
    ++n;
  if (strncmp(ENDINCANT, zappy->current->buffer, strlen(ENDINCANT)) == 0)
    {
      if (!(zappy->current->command[n] = strdup(MICHEL)))
        return (false);
    }
  else if (!(zappy->current->command[n] = strdup(zappy->current->buffer)))
    return (false);
  return (true);
}

static bool	treat_command(t_zappy *zappy)
{
  bool		ret;

  ret = true;
  if (zappy->current_type == VIEWER)
    ret = find_command_viewer(zappy, zappy->current->buffer);
  else if (zappy->current_type == WAITER)
    ret = find_command_waiter(zappy, zappy->current->buffer);
  else if (zappy->current_type == PLAYER)
    ret = add_cmd(zappy);
  if (zappy->current)
    {
      free(zappy->current->buffer);
      zappy->current->buffer = NULL;
      if (ret && !(zappy->current->buffer = calloc(1, 1)))
	return (false);
    }
  return (ret);
}

bool		read_client(t_zappy *zappy, bool canRead)
{
  unsigned int	len;
  bool		treatRet;

  treatRet = true;
  if (canRead && !zappy->current->read_more &&
      rread(zappy->current->fd, zappy->current->ring_buffer) <= 0)
    {
      printf("%s%d\n", DISCONNECTCLIENT, zappy->current->fd);
      remove_client(zappy, zappy->current->fd, zappy->current_type);
      zappy->current = NULL;
      return (true);
    }
  if (!treat_rbuffer(zappy))
    return (false);
  if (zappy->current->treat)
    {
      len = strlen(zappy->current->buffer);
	zappy->current->buffer[len - 1] = '\0';
      if (len > 2 && zappy->current->buffer[len - 2] == '\r')
	zappy->current->buffer[len - 2] = '\0';
      treatRet = treat_command(zappy);
    }
  return (treatRet);
}
