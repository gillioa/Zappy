/*
** expulse_utils.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sat Jul 12 15:28:37 2014 courtu_r
** Last update Sat Jul 12 15:33:58 2014 courtu_r
*/

#include "broadcast.h"

char	*get_ans(t_clientIA *, t_clientIA *, t_zappy *);
int	call_ppo(t_zappy *, t_clientIA *);

void	init_begin(t_zappy *server, t_clientIA *client)
{
  int	frequency;

  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  server->currentRessource = client;
}

int	set_all(t_zappy *server, t_clientIA *client, t_node *node)
{
  t_clientIA	*player;
  char		*ans;

  while (node)
    {
      player = (t_clientIA *)(node->data);
      if (node && player)
	node = node->next;
      if (player != client)
	{
	  client->move[client->direction](server, player);
	  if (!(ans = get_ans(player, client, server)))
	    return (-1);
	  copy_in_buff(ans, player->buff_write);
	  free(ans);
	  if ((player->write = true) && call_ppo(server, player))
	    return (1);
	}
    }
  return (0);
}
