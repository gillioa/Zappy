/*
** free_va_arg.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/utils
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 16:07:48 2014 
** Last update Sun Jul 13 16:07:49 2014 
*/

#include	<stdlib.h>
#include	<stdarg.h>

void	*free_va_arg(int nbparam, ...)
{
  int		i;
  void		*tmp;
  va_list	ap;

  i = -1;
  va_start(ap, nbparam);
  while (++i < nbparam)
    {
      tmp = va_arg(ap, void*);
      free(tmp);
    }
  va_end(ap);
  return (NULL);
}
