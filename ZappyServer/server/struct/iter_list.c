/*
** iter_list.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/struct
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:56:02 2014 
** Last update Sun Jul 13 15:56:03 2014 
*/

#include	<stdlib.h>
#include	"zappy.h"
#include	"list.h"

/*
**	the return val can be modify in ptr_func
*/
int	iter(t_list *list, t_zappy *s,
			 int (*p_func)(t_zappy*, t_node*, t_type, int*))
{
  t_node	*loop;
  int		ret;

  ret = -1;
  loop = list->head;
  while (loop)
    {
      p_func(s, loop, list->type, &ret);
      loop = loop->next;
    }
  return (ret);
}

/*
** Loop do ... and return next
**
*/
int	      iter_routine_next(t_list *list, t_zappy *s,
			 t_node *(*p_func)(t_zappy*, t_node*, t_type, int *))
{
  t_node	*loop;
  int		ret;

  ret = -1;
  loop = list->head;
  while (loop)
    loop = p_func(s, loop, list->type, &ret);
  return (ret);
}

int	iter_list_ret_next(t_list *list, int init,
			   t_node *(*func)(t_list *l, t_node*, t_type, int *))
{
  t_node	*loop;
  int		ret;

  ret = init;
  loop = list->head;
  while (loop)
    loop = func(list, loop, list->type, &ret);
  return (ret);
}
