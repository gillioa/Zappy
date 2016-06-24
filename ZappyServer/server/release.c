/*
** release.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 15:50:09 2014 courtu_r
** Last update Sun Jul 13 15:50:09 2014 courtu_r
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"zappy.h"

int	release_memory(t_zappy *server, int ret)
{
  static t_zappy	*ptrZappy;

  if (server)
    ptrZappy = server;
  else
    {
      if (ptrZappy->map)
	free_map(ptrZappy->map);
      free(ptrZappy->incantation_requirements);
      release_list(ptrZappy->listConn);
      release_list(ptrZappy->listTeam);
      release_list(ptrZappy->listIA);
      release_list(ptrZappy->listGUI);
      release_list(ptrZappy->listEGG);
      release_list(ptrZappy->listWrite);
      printf("%s", get_color_term(DISABLE));
      fflush(stdout);
    }
  return (ret);
}
