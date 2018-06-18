/*
** list_add.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:13:07 2017 Mewen Le Reste
** Last update Mon Jun 26 12:13:12 2017 Mewen Le Reste
*/

#include "list.h"

static bool	list_add_node(t_list **list, void *elem, t_node *next, t_node *prev)
{
  t_node	*node;

  if (!(node = malloc(sizeof(t_node))))
    return (false);
  node->value = elem;
  node->next = next;
  if (next)
    next->prev = node;
  node->prev = prev;
  if (prev)
    prev->next = node;
  reset_head_tail_from(list, node);
  ++(*list)->size;
  return (true);
}

bool		add_front(t_list **list, void *elem)
{
  bool		ret;

  ret = list_add_node(list, elem, (*list)->head, NULL);
  return (ret);
}

bool		add_back(t_list **list, void *elem)
{
  bool		ret;

  ret = list_add_node(list, elem, NULL, (*list)->tail);
  return (ret);
}

bool		add_at(t_list **list, void *elem, unsigned int position)
{
  bool		ret;

  if (position > (*list)->size)
    return (false);
  ret = list_add_node(list, elem, get_node(list, position),
		      get_node(list, (position - 1)));
  return (ret);
}
