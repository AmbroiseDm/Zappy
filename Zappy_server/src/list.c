/*
** list.c for zappy in PSU_2016_zappy/Zappy_server/src/
**
** Made by Mewen Le Reste
** Login   <mewen.lereste@epitech.eu>
**
** Started on  Mon Jun 26 12:13:26 2017 Mewen Le Reste
** Last update Wed Jun 28 14:46:51 2017 Mewen Le Reste
*/

#include "list.h"

t_node		*get_node(t_list **list, unsigned int position)
{
  t_node	*node;

  if (!list || position >= (*list)->size)
    return (NULL);
  node = (*list)->head;
  while (position)
    {
      node = node->next;
      --position;
    }
  return (node);
}

static void	delete_node(t_node *node)
{
  if (node->next)
    delete_node(node->next);
  free(node);
}

void		delete_list(t_list **list)
{
  if ((*list)->head)
    delete_node((*list)->head);
  (*list)->size = 0;
  (*list)->head = NULL;
  (*list)->tail = NULL;
  free(*list);
}

t_list		*init_list()
{
  t_list	*list;

  if (!(list = malloc(sizeof(t_list))))
    return (false);
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return (list);
}

void		reset_head_tail_from(t_list **list, t_node *node)
{
  t_node	*tmp;

  tmp = node;
  if (!node)
    {
      (*list)->head = NULL;
      (*list)->tail = NULL;
      return ;
    }
  while (node->prev)
    node = node->prev;
  (*list)->head = node;
  while (tmp->next)
    tmp = tmp->next;
  (*list)->tail = tmp;
}
