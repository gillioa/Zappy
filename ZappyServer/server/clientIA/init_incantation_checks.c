/*
** init_incantation_checks.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Tue Jul  8 13:27:56 2014 courtu_r
** Last update Sat Jul 12 13:11:50 2014 courtu_r
*/

#include <stdlib.h>
#include "zappy.h"

t_inventory	*init_level_7(t_inventory *inv)
{
  inv[6].content[0] = 0;
  inv[6].content[1] = 2;
  inv[6].content[2] = 2;
  inv[6].content[3] = 2;
  inv[6].content[4] = 2;
  inv[6].content[5] = 2;
  inv[6].content[6] = 1;
  return (inv);
}

t_inventory	*init_level_4_5_6(t_inventory *inv)
{
  inv[3].content[0] = 0;
  inv[3].content[1] = 1;
  inv[3].content[2] = 1;
  inv[3].content[3] = 2;
  inv[3].content[4] = 0;
  inv[3].content[5] = 1;
  inv[3].content[6] = 0;

  inv[4].content[0] = 0;
  inv[4].content[1] = 1;
  inv[4].content[2] = 2;
  inv[4].content[3] = 1;
  inv[4].content[4] = 3;
  inv[4].content[5] = 0;
  inv[4].content[6] = 0;

  inv[5].content[0] = 0;
  inv[5].content[1] = 1;
  inv[5].content[2] = 2;
  inv[5].content[3] = 3;
  inv[5].content[4] = 0;
  inv[5].content[5] = 1;
  inv[5].content[6] = 0;
  return (inv);
}

t_inventory	*init_level_1_2_3(t_inventory *inv)
{
  inv[0].content[0] = 0;
  inv[0].content[1] = 1;
  inv[0].content[2] = 0;
  inv[0].content[3] = 0;
  inv[0].content[4] = 0;
  inv[0].content[5] = 0;
  inv[0].content[6] = 0;

  inv[1].content[0] = 0;
  inv[1].content[1] = 1;
  inv[1].content[2] = 1;
  inv[1].content[3] = 1;
  inv[1].content[4] = 0;
  inv[1].content[5] = 0;
  inv[1].content[6] = 0;

  inv[2].content[0] = 0;
  inv[2].content[1] = 2;
  inv[2].content[2] = 0;
  inv[2].content[3] = 1;
  inv[2].content[4] = 0;
  inv[2].content[5] = 2;
  inv[2].content[6] = 0;
  return (inv);
}

t_inventory	*init_inventories(t_zappy *server)
{
  t_inventory	*invent;

  invent = NULL;
  if ((invent = malloc(sizeof(*(invent)) * (7 + 1))) == NULL)
    return (NULL);
  invent = init_level_1_2_3(invent);
  invent = init_level_4_5_6(invent);
  invent = init_level_7(invent);
  server->incantation_requirements = invent;
  return (invent);
}

t_inventory	*get_inventory_to_comp(int lvl, t_zappy *server)
{
  if (lvl > 0 && lvl < 8)
    return (&(server->incantation_requirements[lvl]));
  else
    return (NULL);
}
