/*
** rbuffer.h for zappy in PSU_2016_zappy/Zappy_server/include/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:13:51 2017 Mewen Le Reste
** Last update Mon Jun 26 12:13:54 2017 Mewen Le Reste
*/

#ifndef RBUFFER_H_
# define RBUFFER_H_

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_rbuffer
{
  char		*buffer;
  uint16_t	end;
  uint16_t	index;
  uint16_t	size;
}		t_rbuffer;

void		rfree(t_rbuffer *);
bool		rincrease(t_rbuffer *);
t_rbuffer	*rmalloc(uint16_t);
int		rread(int, t_rbuffer *);

#endif /* !RBUFFER_H_ */
