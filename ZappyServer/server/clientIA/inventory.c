/*
** inventory.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 12:02:12 2014 courtu_r
** Last update Sun Jul 13 21:29:08 2014 courtu_r
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "clients.h"
#include "inventory.h"

int	inventory(t_zappy *server, t_clientIA *client, char *cmd)
{
  char		*msg;
  double	frequency;

  (void)cmd;
  frequency = ((double)1.0f / server->delay);
  client->lastAction = get_tick(frequency);
  msg = get_inventory(client->inventory);
  if (msg)
    {
      copy_in_buff(msg, client->buff_write);
      client->write = true;
      free(msg);
    }
  else
    return (1);
  return (0);
}

t_inventory	*random_init(t_inventory *inventory)
{
  Uint	spawn;
  Uint	res;

  if (inventory == NULL && (inventory = malloc(sizeof(*inventory))) == NULL)
    return (NULL);
  res = 0;
  spawn = rand() % (MAX_RESOURCES + 1);
  while (res < 7)
    inventory->content[res++] = 0;
  if (spawn < MIN_RESOURCES)
    spawn = MIN_RESOURCES;
  while (spawn > 0)
    {
      res = random() % 7;
      if (res != Food)
	inventory->content[res] += 1;
      else
	inventory->content[res] += 126;
      spawn -= 1;
    }
  return (inventory);
}

t_inventory	*init_inventory(t_inventory *inventory)
{
  if (inventory == NULL && (inventory = malloc(sizeof(*inventory))) == NULL)
    return (NULL);
  inventory->content[Food] = 1260;
  inventory->content[Linemate] = 0;
  inventory->content[Deraumere] = 0;
  inventory->content[Sibur] = 0;
  inventory->content[Mendiane] = 0;
  inventory->content[Phiras] = 0;
  inventory->content[Thystame] = 0;
  return (inventory);
}

int	del_resource(e_resource resource, Uint nb, t_inventory *inventory)
{
  Uint	keep;

  keep = inventory->content[resource];
  if (resource < 7 && resource != Food)
    inventory->content[resource] -= nb;
  else if (resource == Food)
    inventory->content[resource] -= nb * 126;
  else
    return (1);
  if (inventory->content[resource] > keep)
    inventory->content[resource] = 0;
  return (0);
}

char	*get_inventory(t_inventory *inventory)
{
  char	*test = malloc(sizeof(*test) * (get_length(inventory) + 1));

  sprintf(test,
  "{nourriture %d, sibur %d, phiras %d, linemate %d, \
thystame %d, mendiane %d, deraumere %d}\n",
		inventory->content[Food],
		inventory->content[Sibur],
		inventory->content[Phiras],
		inventory->content[Linemate],
		inventory->content[Thystame],
		inventory->content[Mendiane],
		inventory->content[Deraumere]);
  return (test);
}
