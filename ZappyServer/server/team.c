/*
** team.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 15:49:46 2014 courtu_r
** Last update Sun Jul 13 15:49:46 2014 courtu_r
*/

#include	<string.h>
#include	<stdlib.h>
#include	"zappy.h"

t_team	*is_in_list_of_team(t_list *list, const char *name)
{
  t_team	*team;
  t_node	*loop;

  if (list->type != TEAM)
    return (NULL);
  loop = list->head;
  while (loop)
    {
      team = ((t_team*)loop->data);
      if (strcmp(name, team->name) == 0)
	return (team);
      loop = loop->next;
    }
  return (NULL);
}

t_clientIA	*is_in_list_of_ia(t_list *list, t_team *team)
{
  t_clientIA	*client;
  t_node	*loop;

  if (list->type != IA)
    return (NULL);
  loop = list->head;
  while (loop)
    {
      client = ((t_clientIA*)loop->data);
      if ((client->socket == -1) && (team == client->team))
	return (client);
      loop = loop->next;
    }
  return (NULL);
}
