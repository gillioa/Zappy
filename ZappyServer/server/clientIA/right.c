/*
** right.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 12:26:31 2014 courtu_r
** Last update Sun Jul 13 21:25:30 2014 courtu_r
*/

#include	"zappy.h"

int	call_ppo(t_zappy *, t_clientIA *);

int	right(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	 frequency;

  (void)cmd;
  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  if (client->direction < Left)
    client->direction += 1;
  else
    client->direction = Up;
  copy_in_buff("ok\n", client->buff_write);
  client->write = true;
  if (call_ppo(server, client))
    return (1);
  return (0);
}
