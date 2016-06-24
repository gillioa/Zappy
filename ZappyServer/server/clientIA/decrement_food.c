/*
** decrement_food.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 12:13:21 2014 courtu_r
** Last update Sun Jul 13 20:01:38 2014 courtu_r
*/

#include <math.h>
#include "zappy.h"
#include "clients.h"
#include "inventory.h"

int	call_pie(t_zappy *, t_clientIA *, double, int);

void	last_checks(t_zappy *server, t_clientIA *client, bool *ret,
		    bool first_check)
{
  if (!first_check)
    {
      call_pie(server, client, 0.0f, 0);
    }
  client->error = true;
  *ret = false;
}

void	set_end_client(t_clientIA *client)
{
  client->write = true;
  client->lastAction = 0.0f;
  client->call_incantation = false;
}

void	finish_decrement(t_clientIA **client)
{
  copy_in_buff("mort\n", (*client)->buff_write);
  (*client)->write = true;
  (*client)->decLife = 0.0f;
  (*client)->isDead = true;
  (*client)->lastAction = 0.0f;
}

int	decrement_food(t_clientIA *client, t_inventory *inventory,
		       t_zappy *server, t_egg *egg)
{
  inventory->content[Food] -= 126;
  if (inventory->content[Food] <= 0)
    {
      if (!egg)
	{
	  server->currentRessource = client;
	  if (!put_in_list(server->listWrite, create_gui_ans(tograph_pdi(server),
							     client->lastAction)))
	    return (1);
	}
      else
	{
	  server->currentRessource = egg;
	  if (!put_in_list(server->listWrite, create_gui_ans(tograph_edi(server),
							     client->lastAction)))
	    return (1);
	  egg->team->nb_slots_max -= 1;
	}
      finish_decrement(&client);
      return (1);
    }
  else
    return (0);
}

double	get_sign(double *vec_dist, double *vec_comp)
{
  double	s;

  s = (vec_dist[0] * vec_comp[1] - vec_dist[1] * vec_comp[0]);
  if (s < 0.0)
    return (-1.0);
  else
    return (1.0);
}
