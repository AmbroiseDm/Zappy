/*
** list_del.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:13:17 2017 Mewen Le Reste
** Last update Tue Jun 27 21:46:46 2017 Mewen Le Reste
*/

#include "list.h"

static bool	del_node(t_list **list, t_node *entry)
{
  t_node	*tmp;
  t_node	**indirect;

  if (!entry)
    return (false);
  indirect = &(*list)->head;
  while ((*indirect) != entry)
    indirect = &(*indirect)->next;
  tmp = *indirect;
  if (entry->next)
    entry->next->prev = entry->prev;
  *indirect = entry->next;
  --(*list)->size;
  if (entry->next)
    reset_head_tail_from(list, entry->next);
  else
    reset_head_tail_from(list, entry->prev);
  free(tmp);
  return (true);
}

bool		del_front(t_list **list)
{
  bool		ret;

  ret = del_node(list, (*list)->head);
  return (ret);
}

bool		del_back(t_list **list)
{
  bool		ret;

  ret = del_node(list, (*list)->tail);
  return (ret);
}

bool		del_at(t_list **list, unsigned int position)
{
  bool		ret;

  ret = del_node(list, get_node(list, position));
  return (ret);
}
