/*
** incantation.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 13:58:12 2014 courtu_r
** Last update Sun Jul 13 19:47:55 2014 courtu_r
*/

#include	<string.h>
#include	<stdlib.h>
#include	"proto.h"
#include	"zappy.h"

void	last_checks(t_zappy *, t_clientIA *, bool *, bool);
void	set_end_client(t_clientIA *);
int	call_pic(t_zappy *, t_clientIA *, double);
int	call_pie(t_zappy *, t_clientIA *, double, int);
int	call_plv(t_zappy *, t_clientIA *, double);
bool    has_enough_players(t_list *, int, int);
bool	has_all_resources(t_inventory *, t_inventory *);

char	*get_message(bool first_check, int level)
{
  char	*msg;

  if (first_check)
    return (strdup("elevation en cours\n"));
  else
    {
      if (!(msg = malloc(sizeof(*msg) * (18 + 1))))
	return (NULL);
      sprintf(msg, "niveau actuel : %d\n", level);
      return (msg);
    }
}

bool	level_up_players(t_case *pos, int level, t_clientIA *incanter,
			 t_zappy *server)
{
  t_node	*node;
  t_clientIA	*client;
  char	*msg;

  node = pos->players->head;
  msg = NULL;
  call_pie(server, incanter, 0.0f, 1);
  while (node)
    {
      client = (t_clientIA *)(node->data);
      if (client->level == level)
	client->level += 1;
      if (client->level == 8)
	set_end_game(server, client);
      call_plv(server, client, 0.0f);
      if (client != incanter)
	{
	  if (!(msg = get_message(false, client->level)))
	    return (false);
	  client->incantation = msg;
	}
      node = node->next;
    }
  return (true);
}

bool	init_beg(t_zappy *server, t_clientIA *client, t_case **pos,
		 bool *has_resources)
{
  int	x;
  int	y;
  int	level;

  level = client->level;
  x = correct_x(client->x, server);
  y = correct_y(client->y, server);
  *pos = server->map->map[y][x];
  *has_resources = has_all_resources(&(server->
				       incantation_requirements[level - 1]),
				     (*pos)->inventory);
  return (has_enough_players((*pos)->players, level, server->
			     nb_players[level - 1]));
}

bool	are_requirements_met(t_zappy *server, t_clientIA *client,
			     bool first_check)
{
  bool		ret;
  bool		has_resources;
  bool		has_players;
  t_case	*pos;
  char		*msg;

  pos = NULL;
  has_players = init_beg(server, client, &pos, &has_resources);
  if (has_resources && has_players)
    {
      if (first_check)
	call_pic(server, client, 0.0f);
      if (!first_check)
	level_up_players(pos, client->level, client, server);
      if (!(msg = get_message(first_check, client->level)))
	return (false);
      copy_in_buff(msg, client->buff_write);
      free(msg);
      ret = true;
    }
  else
    last_checks(server, client, &ret, first_check);
  if (!first_check)
    set_end_client(client);
  return (ret);
}

int	incantation(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	frequency;
  bool		cond;

  (void)cmd;
  frequency = ((double)300.0f / server->delay);
  client->call_incantation = true;
  client->lastAction = get_tick(frequency);
  cond = are_requirements_met(server, client, true);
  if (!cond)
    {
      client->lastAction = 0.0f;
      client->call_incantation = false;
    }
  return (0);
}
