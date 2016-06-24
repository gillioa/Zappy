/*
** see.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 13:59:31 2014 courtu_r
** Last update Sun Jul 13 19:49:13 2014 courtu_r
*/

#include	<string.h>
#include	"proto.h"
#include	"zappy.h"

void	set_end_game(t_zappy *server, t_clientIA *client)
{
  server->game = false;
  server->currentRessource = client->team;
  if (!(put_in_list(server->listWrite, create_gui_ans(tograph_seg(server),
						      0.0f))))
    return ;
}

char	*add_resources(t_inventory invent, int nb_resources, t_zappy *server,
		       char *msg)
{
  int	i;

  i = 0;
  while (nb_resources > 0 && i < 7)
    {
      if (invent.content[i] < 1)
	i += 1;
      else
	{
	  if ((msg = realloc
	       (msg,
		sizeof(*msg) * (my_strlen(msg) + my_strlen
				(server->resources[i]) + 2)
		)) == NULL)
	    return (NULL);
	  msg = strcat(msg, server->resources[i]);
	  nb_resources -= 1;
	  invent.content[i] -= get_ressources_to_sub(i);
	  if (nb_resources)
	    msg = strcat(msg, " ");
	}
    }
  return (msg);
}

char	*serialize_case(t_case *pos, char *msg, t_zappy *server)
{
  if ((msg = add_players(count_nb_players(pos->players), msg, server)) == NULL)
    return (NULL);
  if ((msg = realloc(msg, sizeof(*msg) * (strlen(msg) + 2))) == NULL)
    return (NULL);
  if ((msg = strcat(msg, " ")) == NULL)
    return (NULL);
  if ((msg = add_resources(*(pos->inventory), cnt_nb_resources(pos->inventory),
			   server, msg)) == NULL)
    return (NULL);
  return (msg);
}

char	*get_left_right(t_zappy *server, char *msg, t_clientIA *player)
{
  int	width;
  int	depth;
  int	tmpX;
  int	tmpY;
  int	nbcases;
  int	cnt;

  nbcases = get_nb_cases(player->level);
  init_int_var_left_right(&width, &depth, &cnt);
  init_pos_player_left_right(&tmpX, &tmpY, player);
  while (depth <= player->level) {
    while (cnt < width)	{
      if ((msg = serialize_case(server->map->map[tmpY]
				[correct_x(tmpX, server)], msg,
				server)) == NULL)
	return (NULL);
      if (mid_loop_left_right(&nbcases, &cnt, &msg) == -1)
	return (NULL);
      f_cor_saw_left_right(player, &tmpY, server);
    }
    looping_left_right(&cnt, &width, &depth);
    cor_saw_left_right(player, &tmpY, width, server);
    tmpX = correct_x(tmpX + (player->x_moves[player->direction]), server);
  }
  return (msg);
}

int	see(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	 frequency;
  char		*msg = NULL;

  if (!(msg = malloc(sizeof(*msg) * 2)))
    return (-1);
  msg[0] = '{';
  msg[1] = 0;
  (void)cmd;
  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  if (client->direction == Up || client->direction == Down)
    msg = get_up_down(server, msg, client);
  else if (client->direction == Right || client->direction == Left)
    msg = get_left_right(server, msg, client);
  if ((msg = realloc(msg, sizeof(*msg) * (strlen(msg) + 3))) == NULL)
    return (-1);
  if ((msg = strcat(msg, "}\n")) == NULL)
    return (-1);
  client->big_write = msg;
  return (0);
}
