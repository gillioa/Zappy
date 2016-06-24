/*
** routine_egg.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/egg
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:55:32 2014 
** Last update Sun Jul 13 15:55:33 2014 
*/

#include	<stdlib.h>
#include	"zappy.h"

t_node	*routine_egg(t_zappy *s, t_node *node, t_type type, int *ret)
{
  t_egg		*egg;

  (void)ret;
  if (type != EGG)
    return (NULL);
  egg = ((t_egg*)node->data);
  if (egg && (!(egg->active)) && (egg->tick < get_tick(0)))
    hatch_egg(egg, s);
  if (egg && (egg->active))
    {
      if (decrement_food(egg->player, egg->player->inventory, s, egg) == 1)
	return (rm_node(s->listEGG, node));
      egg->tick = get_tick(((double)UNIT_TIME / s->delay));
    }
  return (node->next);
}
