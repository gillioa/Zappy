/*
** left.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 13:11:08 2014 courtu_r
** Last update Sun Jul 13 19:44:13 2014 courtu_r
*/

#include	"broadcast.h"

int	call_ppo(t_zappy *server, t_clientIA *client)
{
  server->currentRessource = client;
  char	*str = tograph_ppo(server);
  if (!put_in_list(server->listWrite, create_gui_ans(str, client->lastAction)))
    return (1);
  return (0);
}

int	left(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	 frequency;

  (void)cmd;
  frequency = ((double)7 / server->delay);
  client->lastAction = get_tick(frequency);
  if (client->direction > 0)
    client->direction -= 1;
  else
    client->direction = Left;
  copy_in_buff("ok\n", client->buff_write);
  client->write = true;
  if (call_ppo(server, client))
    return (1);
  return (0);
}
