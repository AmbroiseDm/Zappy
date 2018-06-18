/*
** linked_list.h for zappy in PSU_2016_zappy/Zappy_server/include/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Wed Jun 28 14:10:54 2017 Mewen Le Reste
** Last update Wed Jun 28 14:12:20 2017 Mewen Le Reste
*/

#ifndef LIST_H_
# define LIST_H_

# include <stdlib.h>
# include <stdbool.h>

typedef struct	s_node
{
  void		*value;
  struct s_node	*next;
  struct s_node	*prev;
}		t_node;

typedef struct	s_list
{
  t_node	*head;
  t_node	*tail;
  unsigned int	size;
}		t_list;

t_list		*init_list();
void		delete_list(t_list **);
void		reset_head_tail_from(t_list **, t_node *);
t_node		*get_node(t_list **, unsigned int);
bool		add_front(t_list **, void *);
bool		add_back(t_list **, void *);
bool		add_at(t_list **, void *, unsigned int);
bool		del_front(t_list **);
bool		del_back(t_list **);
bool		del_at(t_list **, unsigned int);

#endif /* !LIST_H_ */
