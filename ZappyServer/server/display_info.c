/*
** display_info.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sun Jul 13 15:50:29 2014 courtu_r
** Last update Sun Jul 13 19:38:12 2014 courtu_r
*/

#include	<sys/time.h>
#include	<stdlib.h>
#include	"zappy.h"

#define LISTEN		"Listening on port %d...\n"
#define CONF		"Configuration : Max(%d) WordX(%d) WorldY(%d) Delay(%d)\n"
#define	NAME_TEAM	"\tName(%s) Max(%d)\n"

static int print_info_team(t_zappy *server, t_node *node,
			   t_type type, int *ret);

int	display_info(t_zappy *server)
{
  printf("%s", get_color_term(SERVER));
  printf(LISTEN, server->port);
  printf(CONF, server->nbClients, server->width, server->height,
	 server->delay);
  printf("Teams :\n");
  iter(server->listTeam, server, print_info_team);
  printf("Server is ready !!!%s\n", get_color_term(DISABLE));
  return (0);
}

static int print_info_team(t_zappy *server, t_node *node, t_type type,
			   int *ret)
{
  t_team	*team;

  (void)ret;
  (void)server;
  if (type != TEAM)
    return (1);
  team = ((t_team*)node->data);
  printf(NAME_TEAM, team->name, team->nb_slots_max);
  return (0);
}

void	print_time_param(double time)
{
  TIMEVAL	tv;

  tv.tv_sec = time / 1000000.0f;
  while (time > 10000000000.0f)
    time -= 10000000000.0f;
  while (time > 100000000.0f)
    time -= 100000000.0f;
  while (time > 1000000.0f)
    time -= 1000000.0f;
  tv.tv_usec = time;
  printf("%d:%06d\n", ((int)tv.tv_sec), ((int)tv.tv_usec));
}

int	can_write_buffer(t_buff *buff)
{
  char	*tmp;

  tmp = (buff->begPtr);
  while (*tmp != '\n' && tmp != buff->endPtr)
    {
      tmp += 1;
      if (tmp > buff->buf + SIZE)
	tmp = buff->buf;
    }
  if (*tmp == '\n')
    return (1);
  else
    return (0);
}

void	print_cmd_buffer(t_buff *buff)
{
  char	*tmp;

  tmp = (buff->begPtr);
  while (*tmp != '\n' && tmp != buff->endPtr)
    {
      printf("%c", *tmp);
      tmp += 1;
      if (tmp >= buff->buf + SIZE)
	tmp = buff->buf;
    }
  printf("\n");
}
