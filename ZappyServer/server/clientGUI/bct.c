/*
** bct.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientGUI
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:53:00 2014
** Last update dim. juil. 13 16:36:07 2014 julien thebaud
*/

#include	<string.h>
#include	"utils.h"
#include	"zappy.h"
#include	"tograph.h"

int	bct(t_zappy *server, t_clientGUI *client, char *cmd)
{
  unsigned int	x;
  unsigned int	y;
  char		*send;

  if (parse_two_int(cmd, &x, &y))
    {
      client->error = true;
      return (1);
    }
  if ((x >= server->width) || (y >= server->height))
    client->error = true;
  else
    {
      server->currentRessource = ((void*)server->map->map[y][x]);
      send = tograph_bct(server);
      if (send)
	{
	  copy_in_buff(send, client->buff_write);
	  free(send);
	  client->write = true;
	}
    }
  return (0);
}
