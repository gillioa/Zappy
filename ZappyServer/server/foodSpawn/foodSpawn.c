/*
** foodSpawn.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/foodSpawn
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 16:16:29 2014 
** Last update Sun Jul 13 16:16:34 2014 
*/

#include "zappy.h"

void	new_client_spawn_food(t_zappy * z) {
  unsigned int	nb_food;
  unsigned int	i;
  unsigned int	x;
  unsigned int	y;
  char		*str;

  i = -1;
  nb_food = (z->map->width * z->map->height / 2) + 1;
  while (++i < nb_food) {
    x = random() % z->map->width;
    y = random() % z->map->height;
    z->map->map[y][x]->inventory->content[Food] += 126;
    z->currentRessource = z->map->map[y][x];
    if (!(str = tograph_bct(z)))
      return ;
    if (!put_in_list(z->listWrite, create_gui_ans(str, 0.0f)))
      return ;
  }
}

void	timer_spawn_food(t_zappy * z) {
  unsigned int	nb_food;
  unsigned int	i;
  unsigned int	x;
  unsigned int	y;

  i = -1;
  nb_food = (z->map->width * z->map->height / 24) + 1;
  while (++i < nb_food) {
    x = random() % z->map->width;
    y = random() % z->map->height;
    z->map->map[y][x]->inventory->content[Food] += 126;
  }
}
