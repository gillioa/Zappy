/*
** routine_clients_ia.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy/server
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 21:02:10 2014 courtu_r
** Last update Sun Jul 13 21:25:10 2014 courtu_r
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	"zappy.h"
#include	"proto.h"

static int	treat_died(t_zappy *s, t_clientIA *client);
static int	read_node_ia(t_zappy *s, t_clientIA *client);
static int	write_node_ia(t_zappy *s, t_clientIA *client);
static int	actions_node_ia(t_zappy *s, t_clientIA *client);

t_node	*routine_clientIA(t_zappy *s, t_node *node, t_type type, int *ret)
{
  t_clientIA	*client;

  (void)ret;
  if (type != IA)
    return (NULL);
  client = ((t_clientIA*)node->data);
  if (client)
    {
      if ((client->decLife < get_tick(0.0f)))
	{
	  if (decrement_food(client, client->inventory, s, NULL) == 1)
	    client->isDead = true;
	  client->decLife = get_tick(((double)UNIT_TIME / (double)s->delay));
	}
      if (write_node_ia(s, client) == -1)
	return rm_node(s->listIA, node);
      if (read_node_ia(s, client) == -1)
	return rm_node(s->listIA, node);
      if (actions_node_ia(s, client) == -1)
	return rm_node(s->listIA, node);
    }
  return (node->next);
}

static int	actions_node_ia(t_zappy *s, t_clientIA *client)
{
  char		*str;
  t_cmd_ia	num;

  if (((client->lastAction == 0.0f)
      || (client->lastAction < get_tick(0.0f)))
      && (str = try_get_cmd(client->buff_read)))
    {
      if ((num = find_cmd_ia(str)) != UNKNOWN)
	(*s->ptr_func_ia[num])(s, client, str);
      else
	client->error = true;
      free(str);
    }
  return (0);
}

static int 	write_node_ia(t_zappy *s, t_clientIA *client)
{
  const char	*error = "ko\n";

  if (client->error && FD_ISSET(client->socket, &(s->writesd)))
    write_error_ia(client, error);
  else
    {
      if (((client->lastAction < get_tick(0.0f)))
	  && client->write && FD_ISSET(client->socket, &(s->writesd)))
	write_cmd(client);
      else if (client->broadcast && client->lastAction < get_tick(0.0f))
	call_back_broadcast(s, client);
      else if (client->incantation)
	write_level_up(s, client);
      else if (client->call_incantation)
	write_incantation(s, client);
      else if (client->instant_write && FD_ISSET(client->socket, &(s->writesd)))
	write_buffer_ia(client, &(client->instant_write));
      else if (((client->lastAction < get_tick(0.0f)))
	       && client->big_write && FD_ISSET(client->socket, &(s->writesd)))
	write_buffer_ia(client, &(client->big_write));
    }
  if (client->isDead)
    return (treat_died(s, client));
  return (0);
}

static int	treat_died(t_zappy *s, t_clientIA *client)
{
  send_buffer(client, try_get_cmd(client->buff_write));
  --(client->team->nbplayers);
  --(s->max_id);
  if (close(client->socket) == -1)
    perror("Close failed. Error");
  client->socket = -1;
  return (-1);
}

static int	read_node_ia(t_zappy *s, t_clientIA *client)
{
  if (FD_ISSET(client->socket, &(s->readsd)))
    {
      if (write_in_buff(client->socket, client->buff_read,
			true, client->id) <= 0)
	{
	  printf("%s", get_color_term(SERVER));
	  printf("*** Player %d is now in GHOST mode", client->id);
	  printf("%s\n", get_color_term(DISABLE));
	  client->old_id = client->socket;
	  --(client->team->nbplayers);
	  if (close(client->socket) == -1)
	    perror("Close failed. Error");
	  client->socket = -1;
	  return (1);
	}
    }
  return (0);
}
