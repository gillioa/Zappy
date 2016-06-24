/*
** map_utils.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 16:49:22 2014 courtu_r
** Last update Sun Jul 13 16:50:54 2014 courtu_r
*/

#include	"map.h"

bool	place_player(t_clientIA *player, t_map *map)
{
  if (add_player_to_pos(player, map, player->x, player->y) == false)
    return (false);
  return (true);
}

bool	add_player_to_pos(t_clientIA *player, t_map *map, Uint x, Uint y)
{
  return (add_player(player, map->map[y][x]));
}

void	remove_player_from_pos(t_clientIA *player, t_map *map, Uint x, Uint y)
{
  remove_player(player, map->map[y][x]);
}
