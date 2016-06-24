/*
** see_utils3.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sun Jul 13 16:41:30 2014 courtu_r
** Last update Sun Jul 13 16:44:29 2014 courtu_r
*/

#include	<string.h>
#include	"proto.h"
#include	"zappy.h"

void	init_pos_player_left_right(int * tmpX, int * tmpY, t_clientIA *player)
{
  (*tmpX) = player->x;
  (*tmpY) = player->y;
}

void	looping_left_right(int * cnt, int * width, int * depth)
{
  (*cnt) = 0;
  (*width) += 2;
  (*depth) += 1;
}

int	f_cor_up_down(int * nbcases, int * cnt, char **msg)
{
  (*nbcases) -= 1;
  (*cnt) += 1;
  if ((*nbcases) > 0) {
    if (((*msg) = realloc(*msg, sizeof(**msg) * (strlen(*msg) + 2))) == NULL)
      return (-1);
    if (((*msg) = strcat(*msg, ",")) == NULL)
      return (-1);
  }
  return (0);
}

void	f2_cor_up_down(int * tmpX, t_clientIA * player, t_zappy * server)
{
  if (player->direction == Up)
    (*tmpX) = correct_x((*tmpX) + player->
			x_moves[get_right(player->direction)],
			server);
  else
    (*tmpX) = correct_x((*tmpX) + player->
			x_moves[get_left(player->direction)], server);
}

void	f3_cor_up_down(int * tmpX, t_clientIA * player, t_zappy * server,
		       int width)
{
  if (player->direction == Up)
    (*tmpX) = correct_x(player->
			x + (player->
			     x_moves[get_left(player->
					      direction)
				     ] * (width / 2)),
			server);
  else
    (*tmpX) = correct_x(player->
			x + (player->
			     x_moves[get_right(player->
					       direction)
				     ] * (width / 2)),
			server);
}
