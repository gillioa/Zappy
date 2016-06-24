/*
** signals.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sun Jul 13 15:49:53 2014 courtu_r
** Last update dim. juil. 13 21:42:59 2014 julien thebaud
*/

#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"zappy.h"

static void	handle_signal(int sig)
{
  release_memory(NULL, 0);
  exit(sig);
}

static	void	handle_trick(int sig)
{
  (void)sig;
}

int		init_signal(t_zappy *server)
{
  (void)server;
  if (signal(SIGINT, handle_signal) == SIG_ERR)
    {
      fprintf(stderr, "signal(SIGINT) failed.\n");
      return (1);
    }
  if (signal(SIGQUIT, handle_signal) == SIG_ERR)
    {
      fprintf(stderr, "signal(SIGQUIT) failed.\n");
      return (1);
    }
  if (signal(SIGPIPE, handle_trick) == SIG_ERR)
    {
      fprintf(stderr, "signal(SIGPIPE) failed.\n");
      return (1);
    }
  return (0);
}
