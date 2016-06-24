/*
** connexion.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:59:09 2014 
** Last update Sun Jul 13 15:59:10 2014 
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	"zappy.h"

static t_conn	*alloc_conn(SOCKET sd);

int		connexion(t_zappy *server)
{
  t_conn	*conn;
  int		new_sock;

  if ((new_sock = accept(server->listen, NULL, 0)) == -1)
    {
      perror("Accept failed. Error");
      return (1);
    }
  if (!(conn = alloc_conn(new_sock)))
    return (2);
  if (!(put_in_list(server->listConn, conn)))
    return (3);
  printf("%s", get_color_term(SERVER));
  printf("*** New connexion id: %d", new_sock);
  printf("%s\n", get_color_term(DISABLE));
  return (0);
}

static t_conn	*alloc_conn(SOCKET sd)
{
  t_conn	*ret;

  if (!(ret = malloc(sizeof(*ret))))
    return (NULL);
  if (!(ret->buff_read = alloc_buff()))
    return (free_va_arg(1, ret));
  ret->socket = sd;
  ret->welcome = true;
  ret->write = false;
  ret->deco = false;
  return (ret);
}
