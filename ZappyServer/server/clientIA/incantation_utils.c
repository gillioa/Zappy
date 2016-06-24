/*
** incantation_utils.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sat Jul 12 15:01:32 2014 courtu_r
** Last update Sat Jul 12 15:02:11 2014 courtu_r
*/

#include	<string.h>
#include	<stdlib.h>
#include	"zappy.h"

int	call_pic(t_zappy *server, t_clientIA *client, double tick)
{
  t_incantation_for_players	*ans;

  if (!(ans = malloc(sizeof(*ans))))
    return (1);
  ans->ncase = server->map->map[client->y][client->x];
  ans->listPlayer = ans->ncase->players;
  ans->incanter = client;
  server->currentRessource = ans;
  if (!put_in_list(server->listWrite, create_gui_ans(tograph_pic(server),
						     tick)))
    return (1);
  free(ans);
  return (0);
}

int	call_pie(t_zappy *server, t_clientIA *client, double tick, int cond)
{
  t_incantation_ended	*ans;

  if (!(ans = malloc(sizeof(*ans))))
    return (1);
  ans->ncase = server->map->map[client->y][client->x];
  ans->result = cond;
  server->currentRessource = ans;
  if (!put_in_list(server->listWrite, create_gui_ans(tograph_pie(server),
						     tick)))
    return (1);
  free(ans);
  return (0);
}

int	call_plv(t_zappy *server, t_clientIA *client, double tick)
{
  server->currentRessource = client;
  if (!put_in_list(server->listWrite, create_gui_ans(tograph_plv(server),
						     tick)))
    return (1);
  return (0);
}

bool	has_enough_players(t_list *players, int level, int nb_required)
{
  t_node	*node;
  t_clientIA	*client;
  int		cnt;

  cnt = 0;
  node = players->head;
  while (node)
    {
      client = (t_clientIA *)node->data;
      if (client->level == level)
	cnt += 1;
      node = node->next;
    }
  if (cnt == nb_required)
    return (true);
  return (false);
}

bool	has_all_resources(t_inventory *ref, t_inventory *pos)
{
  int	i;

  i = 0;
  while (i < 7)
    {
      if (ref->content[i] > pos->content[i])
	return (false);
      i += 1;
    }
  return (true);
}
