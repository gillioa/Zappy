/*
** list.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/struct
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:56:10 2014
** Last update dim. juil. 13 15:57:18 2014 julien thebaud
*/

#include	<stdlib.h>
#include	"list.h"

t_list	*create_list(t_type type)
{
  t_list	*ret;

  if (!(ret = malloc(sizeof(*ret))))
    return (NULL);
  ret->type = type;
  ret->length = 0;
  ret->head = NULL;
  ret->end = NULL;
  return (ret);
}

/*
** put an elem at the end of the list
** all data must be allocated
*/
bool	put_in_list(t_list *list, void *data)
{
  t_node	*elem;

  if ((!data) || (!list))
    return (false);
  if (!(elem = malloc(sizeof(*elem))))
    return (false);
  elem->data = data;
  elem->next = NULL;
  if (!(list->head))
    {
      elem->prev = NULL;
      list->head = elem;
      list->end = elem;
    }
  else
    {
      elem->prev = list->end;
      list->end->next = elem;
      list->end = elem;
    }
  ++(list->length);
  return (true);
}

/*
**	RM node and return the next elem or NULL
*/
t_node	*rm_node(t_list *list, t_node *node)
{
  t_node	*next;

  if ((!list) || (!node))
    return (NULL);
  next = node->next;
  if (node == list->head)
    list->head = next;
  if (node == list->end)
    list->end = node->prev;
  if (node->prev)
    node->prev->next = next;
  if (node->next)
    node->next->prev = node->prev;
  release_node(node, list->type);
  --(list->length);
  return (next);
}

int	release_list(t_list *list)
{
  t_node	*loop;

  if (!(list))
    return (1);
  loop = list->head;
  while (loop)
    loop = rm_node(list, loop);
  free(list);
  return (0);
}
