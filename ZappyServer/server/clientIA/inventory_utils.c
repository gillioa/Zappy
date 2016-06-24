/*
** inventory_utils.c for Zappu in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sat Jul 12 12:09:26 2014 courtu_r
** Last update Sat Jul 12 12:10:17 2014 courtu_r
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "clients.h"
#include "inventory.h"

int	get_pow(int nb)
{
  int	cnt;

  cnt = 1;
  while (nb > 10)
    {
      nb /= 10;
      cnt += 1;
    }
  return (cnt);
}

int	get_length(t_inventory *inventory)
{
  int	cnt;
  int	ret;

  cnt = 0;
  ret = 83;
  while (cnt < 7)
    {
      ret += get_pow(inventory->content[cnt]);
      cnt += 1;
    }
  return (ret);
}

void	print_inventory(t_inventory *inventory)
{
  printf("Inventory contents :\n\t- Food : %d\n\t- Linemate : %d\n",
	 inventory->content[0], inventory->content[1]);
  printf("\t- Deraumere : %d\n", inventory->content[2]);
  printf("\t- Sibur : %d\n\t- Mendiane : %d\n\t- Phiras : %d\n",
	 inventory->content[3], inventory->content[4], inventory->content[5]);
  printf("\t- Thystame : %d\n", inventory->content[6]);
}

int	add_resource(e_resource resource, Uint nb, t_inventory *inventory)
{
  if (resource < 7 && resource != Food)
    inventory->content[resource] += nb;
  else if (resource == Food)
    inventory->content[resource] += nb * 126;
  else
    return (1);
  return (0);
}

int	get_nb_resource(e_resource resource, t_inventory *inventory)
{
  if (resource < 7 && resource != Food)
    return (inventory->content[resource]);
  else if (resource < 7)
    return (inventory->content[Food] / 126);
  else
    return (-1);
}

