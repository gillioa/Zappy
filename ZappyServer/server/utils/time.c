/*
** time.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/utils
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 16:08:05 2014
** Last update dim. juil. 13 16:08:37 2014 julien thebaud
*/

#include	<sys/time.h>
#include	<stdlib.h>
#include	"zappy.h"
void	print_time_param(double);

double		get_tick(double sec)
{
  TIMEVAL	tv;
  double	ret;

  gettimeofday(&tv, NULL);
  ret = ((((double)tv.tv_sec) * 1000000.0f) + (((double)tv.tv_usec)));
  ret += (sec * 1000000.0f);
  return (ret);
}
