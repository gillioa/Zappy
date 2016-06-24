/*
** routine_connexion.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:58:40 2014
** Last update dim. juil. 13 16:57:41 2014 julien thebaud
*/

#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	"zappy.h"

static int	write_node_connexion(t_zappy *s, t_conn *conn);
static int	read_node_connexion(t_zappy *s, t_conn *conn);
static int	actions_node_connexion(t_zappy *s, t_conn *conn);

t_node	*routine_connexion(t_zappy *s, t_node *node, t_type type, int *ret)
{
  t_conn	*conn;

  (void)ret;
  if (type != CONN)
    return (NULL);
  conn = ((t_conn*)node->data);
  if (conn)
    {
      if (write_node_connexion(s, conn) == -1)
	return rm_node(s->listConn, node);
      if (read_node_connexion(s, conn) == -1)
	return rm_node(s->listConn, node);
      if (actions_node_connexion(s, conn) == -1)
	return rm_node(s->listConn, node);
    }
  return (node->next);
}

static int	write_node_connexion(t_zappy *s, t_conn *conn)
{
  const char	*welcome = "BIENVENUE\n";
  const char	*error = "ko\n";
  ssize_t	nbwrites;

  if (conn->welcome && FD_ISSET(conn->socket, &(s->writesd)))
    {
      nbwrites = write(conn->socket, welcome, strlen(welcome));
      if (nbwrites == ((ssize_t)strlen(welcome)))
	conn->welcome = false;
    }
  else if (conn->write && FD_ISSET(conn->socket, &(s->writesd)))
    {
      nbwrites = write(conn->socket, error, strlen(error));
      if (nbwrites == ((ssize_t)strlen(error)))
	conn->write = false;
    }
  return (0);
}

static int	read_node_connexion(t_zappy *s, t_conn *conn)
{
  if (FD_ISSET(conn->socket, &(s->readsd)))
    {
      if (write_in_buff(conn->socket, conn->buff_read,
			false, 0) <= 0)
	{
	  if (close(conn->socket) == -1)
	    perror("Close failed. Error");
	  return (-1);
	}
    }
  return (0);
}

static int	actions_node_connexion(t_zappy *s, t_conn *conn)
{
  char		*str;
  int		ret;
  int		len;

  while ((str = try_get_cmd(conn->buff_read)))
    {
      len = strlen(str);
      if (str[len - 1] != '\n')
	{
	  free(str);
	  conn->write = true;
	  return (1);
	}
      str[len - 1] = '\0';
      ret = choose_graphic_or_ia(s, conn, str);
      free(str);
      return (ret);
    }
  return (0);
}
