/*
** move.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 12:23:41 2014 courtu_r
** Last update sam. juil. 12 19:18:07 2014 julien thebaud
*/

#include	"zappy.h"
#include	"tograph.h"

int	call_ppo(t_zappy *, t_clientIA *);

int	move_up(t_zappy *server, t_clientIA *client)
{
  remove_player_from_pos(client, server->map, client->x, client->y);
  if (client->y > 0)
    client->y -= 1;
  else
    client->y = server->map->height - 1;
  add_player_to_pos(client, server->map, client->x, client->y);
  return (0);
}

int	move_right(t_zappy *server, t_clientIA *client)
{
  remove_player_from_pos(client, server->map, client->x, client->y);
  if (client->x < server->map->width - 1)
    client->x += 1;
  else
    client->x = 0;
  add_player_to_pos(client, server->map, client->x, client->y);
  return (0);
}

int	move_down(t_zappy *server, t_clientIA *client)
{
  remove_player_from_pos(client, server->map, client->x, client->y);
  if (client->y < server->map->height - 1)
    client->y += 1;
  else
    client->y = 0;
  add_player_to_pos(client, server->map, client->x, client->y);
  return (0);
}

int	move_left(t_zappy *server, t_clientIA *client)
{
  remove_player_from_pos(client, server->map, client->x, client->y);
  if (client->x > 0)
    client->x -= 1;
  else
    client->x = server->map->width - 1;
  add_player_to_pos(client, server->map, client->x, client->y);
  return (0);
}

int	move(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	 frequency;

  (void)cmd;
  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  client->move[client->direction](server, client);
  copy_in_buff("ok\n", client->buff_write);
  client->write = true;
  if (call_ppo(server, client))
    return (1);
  return (0);
}
