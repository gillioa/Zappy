/*
** routine_clients_gui.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:58:32 2014
** Last update dim. juil. 13 17:47:46 2014 julien thebaud
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	"zappy.h"

static int	read_node_gui(t_zappy *s, t_clientGUI *client);
static int	write_node_gui(t_zappy *s, t_clientGUI *client);
static int	actions_node_gui(t_zappy *s, t_clientGUI *client);
static int	error_node_gui(t_zappy *s, t_clientGUI * client);

t_node	*routine_clientGUI(t_zappy *s, t_node *node, t_type type, int *ret)
{
  t_clientGUI	*client;

  (void)ret;
  if (type != GUI)
    return (NULL);
  client = ((t_clientGUI*)node->data);
  if (client)
    {
      if (error_node_gui(s, client) == -1)
	return rm_node(s->listGUI, node);
      if (read_node_gui(s, client) == -1)
	return rm_node(s->listGUI, node);
      if (actions_node_gui(s, client) == -1)
	return rm_node(s->listGUI, node);
      if (write_node_gui(s, client) == -1)
	return rm_node(s->listGUI, node);
    }
  return (node->next);
}

static int	actions_node_gui(t_zappy *s, t_clientGUI *client)
{
  char		*str;
  t_cmd_gui	num;

  if ((str = try_get_cmd(client->buff_read)))
    {
      if ((num = find_cmd_gui(str)) != NONE)
	(*s->ptr_func_gui[num])(s, client, str);
      else
	client->error = true;
      free(str);
    }
  return (0);
}

static int 	write_node_gui(t_zappy *s, t_clientGUI *client)
{
  const char	*error = "suc\n";
  ssize_t	nbwrites;

  if (client->error && FD_ISSET(client->socket, &(s->writesd)))
    {
      nbwrites = write(client->socket, error, strlen(error));
      if (nbwrites != ((ssize_t)strlen(error)))
	fprintf(stderr, "send() failed.\n");
      client->error = false;
    }
  else
    write_gui(s, client);
  return (0);
}

static int	read_node_gui(t_zappy *s, t_clientGUI *client)
{
  if (FD_ISSET(client->socket, &(s->readsd)))
    {
      if (write_in_buff(client->socket, client->buff_read,
			false, 0) <= 0)
	{
	  printf("Déco client GUI :%d\n", client->socket);
	  if (close(client->socket) == -1)
	    perror("Close failed. Error");
	  return (-1);
	}
    }
  return (0);
}

static int	error_node_gui(t_zappy *s, t_clientGUI *client)
{
  if (FD_ISSET(client->socket, &(s->exceptsd)))
    {
      fprintf(stderr, "Except on socket client\n");
      if (close(client->socket) == -1)
	perror("Close failed. Error");
      client->socket = -1;
      return (-1);
    }
  return (0);
}
