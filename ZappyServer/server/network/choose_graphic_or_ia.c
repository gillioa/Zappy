/*
** choose_graphic_or_ia.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:58:15 2014
** Last update Sun Jul 13 20:08:45 2014 courtu_r
*/

#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<stdbool.h>
#include	"zappy.h"

static int	create_client_gui(t_zappy *, t_conn*);
static void	finish_client(t_zappy *, t_clientIA *, t_team *, t_conn *);

int	choose_graphic_or_ia(t_zappy *s, t_conn *c, const char *buff)
{
  t_team	*team;

  if (strcmp(buff, HOME_GUI) == 0)
    return (create_client_gui(s, c));
  else if ((team = is_in_list_of_team(s->listTeam, buff)))
    {
      if (team->nbplayers >= team->nb_slots_max)
	{
	  printf("%s", get_color_term(SERVER));
	  printf("Deconnexion because team %s is already full", team->name);
	  printf("%s\n", get_color_term(DISABLE));
	  write(c->socket, "ko\n", 3);
	  close(c->socket);
	  return (-1);
	}
      return (choose_client(s, team, c));
    }
  else
    {
      write(c->socket, "ko\n", 3);
      close(c->socket);
      return (-1);
    }
  return (0);
}

int	create_client_ia(t_zappy *s, t_conn* c, t_team *team)
{
  t_clientIA	*clientIA;

  if (!(clientIA = alloc_clientIA(team, c->socket)))
    return (0);
  clientIA->x = rand() % s->width;
  clientIA->y = rand() % s->height;
  if (!(place_player(clientIA, s->map)))
    {
      free(clientIA);
      return (0);
    }
  if (!(put_in_list(s->listIA, clientIA)))
    {
      free(clientIA);
      return (0);
    }
  clientIA->id = ++(s->max_id);
  finish_client(s, clientIA, team, c);
  return (-1);
}

static void	finish_client(t_zappy *s, t_clientIA *c, t_team *t, t_conn *co)
{
  t_gui_answer		*answer;

  printf("%s", get_color_term(SERVER));
  printf("*** Added new player %d at (%d, %d)", c->id, c->x, c->y);
  printf("%s\n", get_color_term(DISABLE));
  c->decLife = get_tick(((double)UNIT_TIME / s->delay));
  ++(t->nbplayers);
  first_send_ia(c, s, t);
  c->buff_read = co->buff_read;
  co->buff_read = NULL;
  s->currentRessource = c;
  answer = create_gui_ans(tograph_pnw(s), 0);
  put_in_list(s->listWrite, answer);
  new_client_spawn_food(s);
}

static int	create_client_gui(t_zappy *s, t_conn* c)
{
  t_clientGUI	*clientGUI;

  if (!(clientGUI = alloc_clientGUI(c->socket)))
    {
      c->write = true;
      return (0);
    }
  if (!(put_in_list(s->listGUI, clientGUI)))
    {
      free(clientGUI);
      c->write = true;
      return (0);
    }
  clientGUI->writeConn = tograph_welcome_msg(s);
  clientGUI->buff_read = c->buff_read;
  c->buff_read = NULL;
  return (-1);
}

void	first_send_ia(t_clientIA *clientIA, t_zappy *s, t_team *team)
{
  char		buffer[50];

  sprintf(buffer, "%d\n", team->nb_slots_max - team->nbplayers);
  copy_in_buff(buffer, clientIA->buff_write);
  sprintf(buffer, "%d %d\n", s->width, s->height);
  copy_in_buff(buffer, clientIA->buff_write);
  clientIA->write = true;
}
