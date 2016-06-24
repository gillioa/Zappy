/*
** sst.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientGUI
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:54:50 2014
** Last update dim. juil. 13 16:37:05 2014 julien thebaud
*/

#include	"utils.h"
#include	"zappy.h"

int	sst(t_zappy *server, t_clientGUI *client, char *cmd)
{
  char		*send;
  unsigned int	delay;

  if (parse_two_int(cmd, &delay, NULL))
    {
      client->error = true;
      return (1);
    }
  if (delay < 1 || delay > 1000000000)
    {
      client->error = true;
      return (1);
    }
  server->delay = delay;
  send = tograph_sgt(server);
  if (send)
    {
      if (!(put_in_list(server->listWrite, create_gui_ans(send, 0))))
	client->error = true;
    }
  return (0);
}
