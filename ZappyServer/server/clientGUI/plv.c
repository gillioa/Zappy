/*
** plv.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientGUI
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:54:01 2014
** Last update dim. juil. 13 16:36:41 2014 julien thebaud
*/

#include	"utils.h"
#include	"zappy.h"

int	plv(t_zappy *server, t_clientGUI *client, char *cmd)
{
  char		*send;
  unsigned int	n;

  if (parse_two_int(cmd, &n, NULL))
    {
      client->error = true;
      return (1);
    }
  server->currentRessource = ((void*)get_clientIA_by_index(server->listIA, n));
  if (server->currentRessource)
    {
      send = tograph_plv(server);
      if (send)
      {
	copy_in_buff(send, client->buff_write);
	free(send);
	client->write = true;
      }
    }
  else
    client->error = true;
  return (0);
}
