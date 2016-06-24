/*
** get_client_ia.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientGUI
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:53:20 2014 
** Last update Sun Jul 13 15:53:22 2014 
*/

#include	<stdlib.h>
#include	"zappy.h"

t_clientIA	*get_clientIA_by_index(t_list *list, unsigned int num)
{
  t_node	*loop;
  t_clientIA	*ret;

  if (list->type != IA)
    return (NULL);
  loop = list->head;
  while (loop)
    {
      ret = ((t_clientIA*)loop->data);
      if (((unsigned int)ret->socket) == num)
	return (ret);
      loop = loop->next;
    }
  return (NULL);
}
