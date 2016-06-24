/*
** see_utils.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 16:24:46 2014 courtu_r
** Last update Sun Jul 13 16:27:28 2014 courtu_r
*/

#include	<string.h>
#include	"zappy.h"

int	my_strlen(char *str)
{
  int	cnt;

  if (!str)
    return (0);
  cnt = 0;
  while (str[cnt])
    cnt += 1;
  return (cnt);
}

int	count_nb_players(t_list	*listIA)
{
  t_node	*elem;
  int		cnt;

  elem = listIA->head;
  cnt = 0;
  while (elem)
    {
      cnt += 1;
      elem = elem->next;
    }
  return (cnt);
}

char	*add_players(int nb_players, char *msg, t_zappy *server)
{
  while (nb_players > 0)
    {
      if ((msg = realloc(msg, sizeof(*msg) * (my_strlen(msg) + my_strlen
					      (server->
					       resources[7]) + 2))
	   ) == NULL)
	return (NULL);
      msg = strcat(msg, server->resources[7]);
      nb_players -= 1;
      if (nb_players)
	msg = strcat(msg, " ");
    }
  return (msg);
}

int	cnt_nb_resources(t_inventory *invent)
{
  int	i;
  int	cnt;

  i = 0;
  cnt = 0;
  while (i < 7)
    {
      cnt += invent->content[i];
      i += 1;
    }
  return (cnt);
}

int	get_ressources_to_sub(int i)
{
  if (i != Food)
    return (1);
  else
    return (126);
}

