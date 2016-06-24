/*
** is_in_list_egg.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/egg
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:55:22 2014 
** Last update Sun Jul 13 15:55:23 2014 
*/

#include	<stdlib.h>
#include	"zappy.h"

static t_clientIA	*create_ia_egg(t_egg *, t_team *, t_zappy *, int);

t_clientIA	*is_in_list_egg(t_list *l, t_team *t, t_conn *c, t_zappy *s)
{
  t_node	*loop;
  t_egg		*egg;
  t_clientIA	*client;
  t_gui_answer	*answer;

  if (l->type != EGG)
    return (NULL);
  loop = l->head;
  while (loop)
    {
      egg = ((t_egg*)loop->data);
      if ((egg->active) && (egg->team == t))
	{
	  s->currentRessource = egg;
	  answer = create_gui_ans(tograph_ebo(s), 0);
	  put_in_list(s->listWrite, answer);
	  client = create_ia_egg(egg, t, s, c->socket);
	  if (client)
	    rm_node(l, loop);
	  return (client);
	}
      loop = loop->next;
    }
  return (NULL);
}

static t_clientIA	*create_ia_egg(t_egg *egg, t_team *team,
				       t_zappy *s, int sd)
{
  t_clientIA	*clientIA;

  if (!(clientIA = alloc_clientIA(team, sd)))
    return (NULL);
  clientIA->x = egg->x;
  clientIA->y = egg->y;
  if (!(place_player(clientIA, s->map)))
    {
      free(clientIA);
      return (NULL);
    }
  if (!(put_in_list(s->listIA, clientIA)))
    {
      free(clientIA);
      return (NULL);
    }
  if (clientIA->buff_read == NULL)
    if (!(clientIA->buff_read = alloc_buff()))
      return (free_va_arg(1, clientIA));
  clientIA->decLife = get_tick(((double)UNIT_TIME * 1.0f / (double)s->delay));
  ++(team->nbplayers);
  first_send_ia(clientIA, s, team);
  return (clientIA);
}
