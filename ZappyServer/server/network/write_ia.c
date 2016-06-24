/*
** write_ia.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:58:49 2014
** Last update dim. juil. 13 20:04:35 2014 julien thebaud
*/

#include	"zappy.h"

void	write_incantation(t_zappy *s, t_clientIA *client)
{
  char		*str;

  if (FD_ISSET(client->socket, &(s->writesd)))
    {
      while ((str = try_get_cmd(client->buff_write)))
	{
	  send_buffer(client, str);
	  free(str);
	}
    }
  if (((client->lastAction < get_tick(0.0f))))
    {
      are_requirements_met(s, client, false);
      client->call_incantation = false;
    }
}

void	write_buffer_ia(t_clientIA *client, char **buff)
{
  send_buffer(client, (*buff));
  free(*buff);
  (*buff) = NULL;
}

void	write_cmd(t_clientIA *client)
{
  char		*str;

  while ((str = try_get_cmd(client->buff_write)))
    {
      send_buffer(client, str);
      free(str);
    }
  client->write = false;
}

void	write_level_up(t_zappy *s, t_clientIA *client)
{
  if (FD_ISSET(client->socket, &(s->writesd)))
    {
      send_buffer(client, client->incantation);
      free(client->incantation);
      client->incantation = NULL;
    }
}

void	do_fd_sets(t_zappy *s, t_clientGUI *client)
{
  if ((client->listWrite->length > 0) || (client->writeConn)
      || (client->write) || (client->error))
    FD_SET(client->socket, &(s->writesd));
  FD_SET(client->socket, &(s->readsd));
  FD_SET(client->socket, &(s->exceptsd));
}
