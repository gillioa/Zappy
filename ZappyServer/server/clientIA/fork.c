/*
** fork.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 13:13:40 2014 courtu_r
** Last update Sun Jul 13 20:54:34 2014 courtu_r
*/

#include	"zappy.h"
#include	"proto.h"

int	hatch_egg(t_egg *egg, t_zappy *server)
{
  egg->tick = 0.0;
  egg->active = true;
  egg->team->nb_slots_max += 1;
  server->currentRessource = egg;
  if (!put_in_list(server->listWrite,
		   create_gui_ans(tograph_eht(server), 0.0f)))
    return (1);
  return (0);
}

t_egg	*set_egg_attrs(t_clientIA *client, t_zappy *server,
		       uint id)
{
  t_egg	*egg;

  // wasd client->socket
  if (!(egg = alloc_egg((uint)id, alloc_clientIA(client->team,
						 client->id))))
    return (NULL);
  egg->player->x = client->x;
  egg->player->y = client->y;
  egg->id = client->id;
  // this is new
  egg->player->id = client->id;
  egg->x = client->x;
  egg->y = client->y;
  egg->tick = ((double)
	       (42.0f / server->delay)) + ((double)
					   (600.0f / server->delay));
  egg->tick = get_tick(egg->tick);
  return (egg);
}

int	_fork(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	frequency;
  int		id;
  t_egg		*egg;

  id = server->listEGG->length + 1;
  (void)cmd;
  frequency = ((double)42.0f / server->delay);
  client->lastAction = get_tick(frequency);
  server->currentRessource = client;
  if (!(egg = set_egg_attrs(client, server, (uint)id)))
    return (1);
  if (!put_in_list(server->listWrite,
		   create_gui_ans(tograph_pfk(server), 0.0)))
    return (1);
  server->currentRessource = egg;
  if (!put_in_list(server->listWrite, create_gui_ans(tograph_enw(server),
						     client->lastAction)))
    return (1);
  egg->player->socket = -1;
  if (!(put_in_list(server->listEGG, egg)))
    return (1);
  copy_in_buff("ok\n", client->buff_write);
  client->write = true;
  return (0);
}
