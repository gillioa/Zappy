/*
** msz.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientGUI
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:53:44 2014
** Last update dim. juil. 13 16:36:27 2014 julien thebaud
*/

#include	"zappy.h"

int	msz(t_zappy *server, t_clientGUI *client, char *cmd)
{
  char		*send;

  (void)cmd;
  send = tograph_msz(server);
  if (send)
    {
      copy_in_buff(send, client->buff_write);
      free(send);
      client->write = true;
    }
  return (0);
}
