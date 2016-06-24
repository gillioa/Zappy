/*
** alloc_client_gui.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientGUI
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:53:09 2014 
** Last update Sun Jul 13 15:53:10 2014 
*/

#include	<stdlib.h>
#include	"zappy.h"

t_clientGUI	*alloc_clientGUI(SOCKET sd)
{
  t_clientGUI	*ret;

  if (!(ret = malloc(sizeof(*ret))))
    return (NULL);
  if (!(ret->buff_write = alloc_buff()))
    return (free_va_arg(1, ret));
  if (!(ret->listWrite = create_list(ANSWER)))
    return (free_va_arg(2, ret->buff_write, ret));
  ret->buff_read = NULL;
  ret->socket = sd;
  ret->error = false;
  ret->write = false;
  ret->writeConn = NULL;
  ret->buff = NULL;
  return (ret);
}
