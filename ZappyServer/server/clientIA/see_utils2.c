/*
** see_utils2.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 16:37:54 2014 courtu_r
** Last update Sun Jul 13 16:38:57 2014 courtu_r
*/

#include	<string.h>
#include	"proto.h"
#include	"zappy.h"

int	correct_y(int y, t_zappy *server)
{
  if (y >= (int)server->height)
    return (y % server->height);
  if (y < 0)
    return (y + server->height);
  return (y);
}

int	correct_x(int x, t_zappy *server)
{
  if (x >= (int)server->width)
    return (x % server->width);
  if (x < 0)
    return (x + server->width);
  return (x);
}

dir	get_right(dir direction)
{
  return ((direction + 1) % 4);
}

dir	get_left(dir direction)
{
  if (direction > Up)
    return (direction - 1);
  else
    return  (Left);
}

int	get_nb_cases(int level)
{
  int	depth;
  int	width;
  int	nbcases;

  nbcases = 0;
  depth = 0;
  width = 1;
  while (depth <= level)
    {
      nbcases += width;
      width += 2;
      depth += 1;
    }
  return (nbcases);
}
