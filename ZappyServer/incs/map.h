/*
** map.h for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Wed Jun 25 12:39:44 2014 courtu_r
** Last update jeu. juin 26 15:49:14 2014 julien thebaud
*/

#ifndef MAP_H__
# define MAP_H__

#include "clients.h"
#include "case.h"

typedef struct s_map
{
  Uint	width;
  Uint	height;
  t_case	***map;
}t_map;

void	free_map(t_map *map);
bool	place_player(t_clientIA *player, t_map *map);
t_map	*init_map(t_map *, Uint, Uint);
t_case	***create_map(Uint, Uint);
bool	add_player_to_pos(t_clientIA *, t_map *, Uint, Uint);
void	remove_player_from_pos(t_clientIA *, t_map *, Uint, Uint);

#endif /*MAP_H__*/
