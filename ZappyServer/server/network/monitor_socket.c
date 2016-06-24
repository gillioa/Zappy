/*
** monitor_socket.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:59:23 2014
** Last update Sun Jul 13 19:51:26 2014 courtu_r
*/

#include	<sys/select.h>
#include	<string.h>
#include	"zappy.h"

static t_gui_answer	*dup_gui_answer(t_gui_answer *old);
static int	set_socket_ia(t_zappy *s, t_node *node, t_type t, int *ret);
static int	set_socket_gui(t_zappy *s, t_node *node, t_type t, int *ret);
static int	set_socket_conn(t_zappy *s, t_node *node, t_type t, int *ret);

void		add_socket_to_monitor(t_zappy *server)
{
  int		ret;
  t_node	*loop;

  FD_ZERO(&(server->readsd));
  FD_ZERO(&(server->writesd));
  FD_ZERO(&(server->exceptsd));
  FD_SET(server->listen, &(server->readsd));
  server->max_sd = server->listen;
  ret = iter(server->listConn, server, set_socket_conn);
  if (server->max_sd < ret)
    server->max_sd = ret;
  ret = iter(server->listIA, server, set_socket_ia);
  if (server->max_sd < ret)
    server->max_sd = ret;
  ret = iter(server->listGUI, server, set_socket_gui);
  if (server->max_sd < ret)
    server->max_sd = ret;
  loop = server->listWrite->head;
  while (loop)
    loop = rm_node(server->listWrite, loop);
}

static int	set_socket_conn(t_zappy *s, t_node *node, t_type t, int *ret)
{
  t_conn	*conn;

  if (t != CONN)
    return (1);
  conn = ((t_conn*)node->data);
  if ((*ret) < conn->socket)
    (*ret) = conn->socket;
  if (conn->welcome)
    FD_SET(conn->socket, &(s->writesd));
  else if (conn->write)
    FD_SET(conn->socket, &(s->writesd));
  FD_SET(conn->socket, &(s->readsd));
  return (0);
}

static int	set_socket_ia(t_zappy *s, t_node *node, t_type t, int *ret)
{
  t_clientIA	*client;

  if (t != IA)
    return (1);
  client = ((t_clientIA*)node->data);
  if (client->socket != -1)
    {
      if ((*ret) < client->socket)
	(*ret) = client->socket;
      if (client->call_incantation || client->broadcast || client->error
	  || client->write || client->instant_write || client->big_write
	  || client->incantation || client->isDead)
	FD_SET(client->socket, &(s->writesd));
      FD_SET(client->socket, &(s->readsd));
    }
  return (0);
}

static t_gui_answer	*dup_gui_answer(t_gui_answer *old)
{
  return (create_gui_ans(strdup(old->msg), old->tick));
}

static int	set_socket_gui(t_zappy *s, t_node *node, t_type t, int *ret)
{
  t_clientGUI	*client;
  t_node	*loop;

  if (t != GUI)
    return (1);
  client = ((t_clientGUI*)node->data);
  if (client->socket != -1)
    {
      if ((*ret) < client->socket)
	(*ret) = client->socket;
      if (s->listWrite->length > 0)
	{
	  loop = s->listWrite->head;
	  while (loop)
	    {
	      put_in_list(client->listWrite,
		      dup_gui_answer(((t_gui_answer*)loop->data)));
	      loop = loop->next;
	    }
	}
      do_fd_sets(s, client);
    }
  return (0);
}
