/*
** display2.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 19:38:01 2014 courtu_r
** Last update Sun Jul 13 19:38:11 2014 courtu_r
*/

#include	<sys/time.h>
#include	<stdlib.h>
#include	"zappy.h"

void	print_time(void)
{
  TIMEVAL	tv;

  gettimeofday(&tv, NULL);
  printf("%d:%06d\t", ((int)tv.tv_sec), ((int)tv.tv_usec));
}
