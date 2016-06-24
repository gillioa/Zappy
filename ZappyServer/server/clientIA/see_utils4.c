/*
** see_utils4.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 16:44:55 2014 courtu_r
** Last update Sun Jul 13 16:48:01 2014 courtu_r
*/

#include	<string.h>
#include	"proto.h"
#include	"zappy.h"

void	init_int_var_left_right(int * width, int * depth, int * cnt)
{
  (*width) = 1;
  (*depth) = 0;
  (*cnt) = 0;
}

char	*get_up_down(t_zappy *server, char *msg, t_clientIA *player)
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
    while (cnt < width) {
      if ((msg = serialize_case(server->map->map[tmpY]
				[correct_x(tmpX, server)], msg,
				server)) == NULL)
	return (NULL);
      if (f_cor_up_down(&nbcases, &cnt, &msg) == -1)
	return (NULL);
      f2_cor_up_down(&tmpX, player, server);
    }
    looping_left_right(&cnt, &width, &depth);
    f3_cor_up_down(&tmpX, player, server, width);
    tmpY = correct_y(tmpY + (player->y_moves[player->direction]), server);
  }
  return (msg);
}

void	cor_saw_left_right(t_clientIA * player, int * tmpY,
			   int width, t_zappy * server)
{
  if (player->direction == Up)
    (*tmpY) = correct_y(player->y + (player->
				     y_moves[get_right(player->direction)
					     ] * (width / 2)), server);
  else
    (*tmpY) = correct_y(player->y + (player->
				     y_moves[get_left(player->direction)
					     ] * (width / 2)), server);
}

void	f_cor_saw_left_right(t_clientIA * player, int * tmpY, t_zappy * server)
{
  if (player->direction == Up)
    (*tmpY) = correct_y((*tmpY) + player->
		     y_moves[get_left(player->direction)], server);
  else
    (*tmpY) = correct_y((*tmpY) + player->
		     y_moves[get_right(player->direction)], server);
}

int	mid_loop_left_right(int * nbcases, int * cnt, char **msg)
{
  (*nbcases) -= 1;
  (*cnt) += 1;
  if ((*nbcases) > 0) {
    if (((*msg) = realloc((*msg), sizeof(**msg) * (strlen(*msg) + 2))) == NULL)
      return (-1);
    if (((*msg) = strcat((*msg), ",")) == NULL)
      return (-1);
  }
  return (0);
}
