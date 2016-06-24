/*
** choose_client.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:59:00 2014
** Last update dim. juil. 13 18:15:07 2014 julien thebaud
*/

#include	<stdlib.h>
#include	"zappy.h"

static int	is_ia(t_zappy *s, t_team *team, t_conn *c);
static int	is_egg(t_zappy *s, t_team *team, t_conn *c);

int	choose_client(t_zappy *server, t_team *team, t_conn *c)
{
  if (is_ia(server, team, c))
    return (-1);
  if (is_egg(server, team, c))
    return (-1);
  return (create_client_ia(server, c, team));
}

static int	is_ia(t_zappy *s, t_team *team, t_conn *c)
{
  t_clientIA	*client;
  t_gui_answer	*answer;

  if ((client = is_in_list_of_ia(s->listIA, team)))
    {
      client->socket = c->socket;
      ++(team->nbplayers);
      first_send_ia(client, s, team);
      s->currentRessource = client;
      answer = create_gui_ans(tograph_pnw(s), 0);
      put_in_list(s->listWrite, answer);
      printf("%s", get_color_term(SERVER));
      printf("*** New player takes over player %d (GHOST) at (%d, %d)",
	client->id, client->x, client->y);
      printf("%s\n", get_color_term(DISABLE));
      client->decLife = get_tick(((double)UNIT_TIME * 1.0f / s->delay));
      return (1);
    }
  return (0);
}

static int	is_egg(t_zappy *s, t_team *team, t_conn *c)
{
  t_clientIA	*client;

  if ((client = is_in_list_egg(s->listEGG, team, c, s)))
    {
      client->socket = c->socket;
      client->id = ++(s->max_id);
      printf("%s", get_color_term(SERVER));
      printf("*** Player %d takes place EGG at (%d, %d)",
	 client->socket, client->x, client->y);
      printf("%s\n", get_color_term(DISABLE));
      client->decLife = get_tick(((double)UNIT_TIME * 1.0f / s->delay));
      return (1);
    }
  return (0);
}
