/*
** alloc_egg.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/egg
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:55:10 2014 
** Last update Sun Jul 13 15:55:11 2014 
*/

#include	<stdlib.h>
#include	"zappy.h"

typedef unsigned int	uint;

t_egg	*alloc_egg(uint id, t_clientIA *client)
{
  t_egg		*ret;

  if (client == NULL)
    return (NULL);
  if (!(ret = malloc(sizeof(*ret))))
    return (NULL);
  ret->id = id;
  ret->x = client->x;
  ret->y = client->y;
  ret->team = client->team;
  ret->player = client;
  ret->active = false;
  ret->tick = 0.0f;
  return (ret);
}
