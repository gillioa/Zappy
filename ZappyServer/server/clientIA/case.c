/*
** case.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ZappyTitou/map
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Mon Jun 23 15:53:43 2014 courtu_r
** Last update Sat Jul 12 13:12:42 2014 courtu_r
*/

#include <stdlib.h>
#include <stdio.h>
#include "clients.h"
#include "case.h"

void	free_case(t_case *to_free)
{
  free(to_free->inventory);
  release_list(to_free->players);
  free(to_free);
}

bool	add_player(t_clientIA *player, t_case *pos)
{
  if (!(put_in_list(pos->players, (void *)(player))))
    return (false);
  return (true);
}

void	remove_player(t_clientIA *player, t_case *pos)
{
  t_list	*players;
  t_node	*node;

  players = pos->players;
  node = players->head;
  while (node)
    {
      if ((t_clientIA *)(node->data) == player)
	{
	  node = rm_node(players, node);
	  node = NULL;
	}
      if (node)
	node = node->next;
    }
}

void	print_case(t_case *this)
{
  printf("Pos x : %d\t--\tPosY : %d\n", this->pos_x, this->pos_y);
  printf("Contents : \n");
  print_inventory((this->inventory));
}

t_case	*init_case(Uint x, Uint y)
{
  t_case	*this;

  if (!(this = malloc(sizeof(*this))))
    return (NULL);
  this->pos_x = x;
  this->pos_y = y;
  this->inventory = NULL;
  this->inventory = random_init((this->inventory));
  this->players = create_list(PLAYER);
  return (this);
}
