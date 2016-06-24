/*
** case.h for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ZappyTitou/map
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Mon Jun 23 15:50:43 2014 courtu_r
** Last update jeu. juil. 10 16:08:26 2014 julien thebaud
*/

#include "list.h"
#include "inventory.h"

#ifndef CASE
# define CASE

typedef struct s_case
{
  t_inventory	*inventory;
  Uint		pos_x;
  Uint		pos_y;
  t_list	*players;
  // Liste de players. Peut pas faire plus pour le moment.
}t_case;

bool	add_player(t_clientIA *, t_case *);
void	remove_player(t_clientIA *, t_case *);
void	free_case(t_case *);
void	print_case(t_case *);
t_case	*init_case(Uint x, Uint y);

#endif /*CASE*/
