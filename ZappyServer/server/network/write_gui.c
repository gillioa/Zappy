/*
** write_gui.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:59:48 2014
** Last update dim. juil. 13 19:54:20 2014 julien thebaud
*/

#include	<stdlib.h>
#include	<string.h>
#include	"zappy.h"
#include	"routines.h"

static void	last_write(t_zappy *s, t_clientGUI *client);

void	write_gui(t_zappy *s, t_clientGUI *client)
{
  ssize_t	nbwrites;

  if (client->writeConn && FD_ISSET(client->socket, &(s->writesd)))
    {
      nbwrites = write(client->socket, client->writeConn,
		       strlen(client->writeConn));
      if (nbwrites != ((ssize_t)strlen(client->writeConn)))
	fprintf(stderr, "send() failed.\n");
      free(client->writeConn);
      client->writeConn = NULL;
    }
  if (client->listWrite->length > 0 && FD_ISSET(client->socket, &(s->writesd)))
    {
      iter_list_ret_next(client->listWrite, client->socket,
			 routine_write_answerGUI);
    }
  last_write(s, client);
}

static void	last_write(t_zappy *s, t_clientGUI *client)
{
  char		*str;
  ssize_t	nbwrites;

  if (client->write && FD_ISSET(client->socket, &(s->writesd)))
    {
      while ((str = try_get_cmd(client->buff_write)))
	{
	  nbwrites = write(client->socket, str, strlen(str));
	  if (nbwrites != ((ssize_t)strlen(str)))
	    fprintf(stderr, "send() failed.\n");
	  free(str);
	}
      client->write = false;
    }
}

t_node	*routine_write_answerGUI(t_list *list, t_node *node,
				 t_type type, int *ret)
{
  char		*str;
  ssize_t	nbwrites;
  t_gui_answer	*answer;

  if (type != ANSWER)
    return (NULL);
  if (!(answer = ((t_gui_answer*)node->data)))
    return (NULL);
  if (answer->tick < ((unsigned int)get_tick(0)))
    {
      str = answer->msg;
      nbwrites = write((*ret), ((char*)str), strlen(str));
      if (nbwrites != ((ssize_t)strlen(str)))
	fprintf(stderr, "send() failed.\n");
      return (rm_node(list, node));
    }
  else
    return (node->next);
}

void    write_error_ia(t_clientIA *client, const char *error)
{
  send_buffer(client, error);
  client->error = false;
}
