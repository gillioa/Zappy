/*
** take_obj.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 12:24:48 2014 courtu_r
** Last update Sun Jul 13 19:48:32 2014 courtu_r
*/

#include	<string.h>
#include	"zappy.h"
#include	"broadcast.h"

char	*get_param(char *);
t_ressourcePlayer	*set_object(t_zappy *, t_clientIA *, int);

int	send_case_inventory(t_zappy *server, t_clientIA *client, t_case *pos)
{
  char	*str;

  server->currentRessource = client;
  if (!(str = tograph_pin(server)))
    return (1);
  if (!put_in_list(server->listWrite, create_gui_ans(str, client->lastAction)))
    return (1);
  server->currentRessource = pos;
  if (!(str = tograph_bct(server)))
    return (1);
  if (!put_in_list(server->listWrite, create_gui_ans(str, client->lastAction)))
    return (1);
  return (0);
}

int	prend_informations(t_zappy *server, t_clientIA *client, int i,
			   t_case *pos)
{
  char	*str;

  if (!(set_object(server, client, i)))
    return (1);
  if (!(str = tograph_pgt(server)))
    return (1);
  if (!put_in_list(server->listWrite, create_gui_ans(str, client->lastAction)))
    return (1);
  free(server->currentRessource);
  if (send_case_inventory(server, client, pos))
    return (1);
  return (0);
}

int	take_obj(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	 frequency;
  char		*resource;
  int		i = 0;
  t_case	*pos;

  pos = server->map->map[client->y][client->x];
  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  resource = get_param(cmd);
  while (i < 7 && strcmp(resource, server->resources[i]))
    i += 1;
  if (i > 6 || get_nb_resource(i, pos->inventory) <= 0)
    {
      client->error = true;
      return (1);
    }
  add_resource(i, 1, client->inventory);
  del_resource(i, 1, pos->inventory);
  if (prend_informations(server, client, i, pos))
    return (1);
  free(resource);
  copy_in_buff("ok\n", client->buff_write);
  client->write = true;
  return (0);
}
