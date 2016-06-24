/*
** map.c for zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy/server/clientIA
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Thu Jun 26 12:46:11 2014 courtu_r
** Last update Sun Jul 13 16:49:41 2014 courtu_r
*/

#include	"proto.h"
#include	"map.h"

t_map	*init_map(t_map *map, Uint width, Uint height)
{
  if (map == NULL && (map = malloc(sizeof(*map))) == NULL)
    return (NULL);
  map->width = width;
  map->height = height;
  map->map = create_map(map->width, map->height);
  return (map);
}

void	free_map(t_map *map)
{
  Uint	x = 0;
  Uint	y = 0;

  while (y < map->height)
    {
      while (x < map->width)
	{
	  free_case(((map->map)[y][x]));
	  x += 1;
	}
      free((map->map)[y]);
      y += 1;
      x = 0;
    }
  free((map->map)[y]);
  free(map->map);
  free(map);
}

t_case	***create_map(Uint width, Uint height)
{
  t_case	***map;
  Uint		x;
  Uint		y;

  x = 0;
  y = 0;
  if ((map = malloc(sizeof(*map) * (height + 1))) == NULL)
    return (NULL);
  while (y < height)
    {
      if ((map[y] = malloc(sizeof(**map) * width)) == NULL)
	{
	  free(map);
	  return (NULL);
	}
      while (x < width)
	{
	  map[y][x] = (init_case(x, y));
	  x += 1;
	}
      y += 1;
      x = 0;
    }
  map[y] = NULL;
  return (map);
}

void	show_map(t_map *map)
{
  Uint	x = 0;
  Uint	y = 0;

  while (y < map->height)
    {
      while (x < map->width)
	{
	  print_case(((map->map)[y][x]));
	  x += 1;
	}
      y += 1;
      x = 0;
    }
}
