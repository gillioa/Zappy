/*
** schedule.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sun Jul 13 15:50:00 2014 courtu_r
** Last update dim. juil. 13 19:14:49 2014 julien thebaud
*/

#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<stdbool.h>
#include	<sys/time.h>
#include	<sys/types.h>
#include	"zappy.h"

int	schedule(t_zappy *server)
{
  int			activity;

  while (server->game)
    {
      server->timeval.tv_sec = 0;
      server->timeval.tv_usec = 5;
      add_socket_to_monitor(server);
      activity = select(server->max_sd + 1, &(server->readsd),
			&(server->writesd), &(server->exceptsd), &(server->timeval));
      if ((activity == -1) && (errno != EINTR))
	perror("Select failed. Error");
      else {
      if (FD_ISSET(server->listen, &(server->readsd)))
	connexion(server);
      if (server->listIA->length > 0)
	iter_routine_next(server->listIA, server, &routine_clientIA);
      if (server->listGUI->length > 0)
	iter_routine_next(server->listGUI, server, &routine_clientGUI);
      if (server->listConn->length > 0)
	iter_routine_next(server->listConn, server, &routine_connexion);
      if (server->listEGG->length > 0)
	iter_routine_next(server->listEGG, server, &routine_egg);
      }
    }
  return (0);
}
