/*
** concatList.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/utils
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 16:07:16 2014 
** Last update Sun Jul 13 16:07:17 2014 
*/

#include	<stdlib.h>
#include	<string.h>
#include	"list.h"

char	*_concatList(t_list *l)
{
  char		*copy_addr;
  char		*content;
  size_t	size;
  t_node	*it;

  size = 0;
  it = l->head;
  content = NULL;
  while (it != NULL)
    {
      size += strlen((char*)it->data);
      content = realloc(content, sizeof(char) * (size + 1));
      copy_addr = content + size - strlen((char*)it->data);
      strcpy(copy_addr, (char*)it->data);
      it = rm_node(l, it);
    }
  return content;
}
