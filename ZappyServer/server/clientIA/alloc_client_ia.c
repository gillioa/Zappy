/*
** alloc_client_ia.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientIA
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:51:17 2014
** Last update Sun Jul 13 20:54:43 2014 courtu_r
*/

#include	<stdlib.h>
#include	"zappy.h"

t_gui_answer	*create_gui_ans(char *msg, unsigned int tick)
{
  t_gui_answer	*ret;

  if (!(ret = malloc(sizeof(*ret))) || msg == NULL)
    return (NULL);
  ret->tick = tick;
  ret->msg = msg;
  return (ret);
}

t_clientIA	*set_attrs(t_clientIA *ret)
{
  ret->error = false;
  ret->write = false;
  ret->level = 1;
  ret->nb_recv = 0;
  ret->move[Up] = move_up;
  ret->move[Right] = move_right;
  ret->move[Down] = move_down;
  ret->move[Left] = move_left;
  ret->direction = rand() % 4;
  ret->x_moves[Up] = 0;
  ret->y_moves[Up] = -1;
  ret->x_moves[Right] = 1;
  ret->y_moves[Right] = 0;
  ret->x_moves[Down] = 0;
  ret->y_moves[Down] = 1;
  ret->x_moves[Left] = -1;
  ret->y_moves[Left] = 0;
  ret->big_write = NULL;
  ret->call_incantation = false;
  ret->isDead = false;
  ret->decLife = 0.0f;
  ret->broadcast = NULL;
  ret->instant_write = NULL;
  return (ret);
}

t_clientIA	*alloc_clientIA(t_team *team, SOCKET sd)
{
  t_clientIA	*ret;

  if (!(ret = malloc(sizeof(*ret))))
    return (NULL);
  if (!(ret->buff_write = alloc_buff()))
    return (free_va_arg(1, ret));
  ret->buff_read = NULL;
  ret->inventory = NULL;
  if (!(ret->inventory = init_inventory(ret->inventory)))
    return (free_va_arg(2, ret->buff_write, ret));
  ret->team = team;
  ret->socket = sd;
  ret->lastAction = 0.0f;
  ret = set_attrs(ret);
  ret->incantation = NULL;
  return (ret);
}
