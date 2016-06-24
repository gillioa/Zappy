/*
** broadcast_utils.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Wed Jul  9 15:30:27 2014 courtu_r
** Last update Sun Jul 13 19:36:48 2014 courtu_r
*/

#include <math.h>
#include "zappy.h"

double	get_shortest_up_down(double y, double dest, t_zappy *server)
{
  int	upy;
  int	downy;
  int	cnt;

  cnt = 0;
  downy = (int)y;
  upy = (int)y;
  while (upy != (int)dest && downy != (int)dest)
    {
      upy -= 1;
      downy += 1;
      if (upy < 0)
	upy = server->height - 1;
      if ((unsigned int)downy >= server->height)
	downy = 0;
      cnt += 1;
    }
  if (upy == (int)dest)
    return ((double)(cnt * -1));
  else
    return ((double)(cnt));
}

double	get_shortest_left_right(double x, double dest, t_zappy *server)
{
  int	leftx;
  int	rightx;
  int	cnt;

  cnt = 0;
  rightx = (int)x;
  leftx = (int)x;
  while (leftx != (int)dest && rightx != (int)dest)
    {
      leftx -= 1;
      rightx += 1;
      if (leftx < 0)
	leftx = server->width - 1;
      if ((unsigned int)rightx >= server->width)
	rightx = 0;
      cnt += 1;
    }
  if (leftx == (int)dest)
    return ((double)(cnt * -1));
  else
    return ((double)cnt);
}

double	*get_shortest_vector(t_clientIA *client_pos, t_clientIA *client_dest,
			     t_zappy *server)
{
  double	*result;

  if (!(result = malloc(sizeof(*result) * (2))))
    return (NULL);
  result[0] = get_shortest_left_right(client_pos->x, client_dest->x, server);
  result[1] = get_shortest_up_down(client_pos->y, client_dest->y, server);
  return (result);
}

int	get_correct_num(double angle)
{
  angle = (360.0 + angle);
  if (angle > 360.0)
    angle -= 360.0;
  if ((int)angle < 45)
    return (1);
  else if ((int)angle == 45)
    return (2);
  else if ((int)angle < 135)
    return (3);
  else if ((int)angle == 135)
    return (4);
  else if ((int)angle < 225)
    return (5);
  else if ((int)angle == 225)
    return (6);
  else if ((int)angle < 315)
    return (7);
  else if ((int)angle == 315)
    return (8);
  else
    return (1);
}

double	scal_prod(double *vec1, double *vec2, bool is_normalized)
{
  if (!is_normalized)
    return (vec1[0] * vec2[0] + vec1[1] * vec2[1]);
  else
    return (sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1]) *
	    sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1]));
}
