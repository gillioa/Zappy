/*
** func_parse2.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/init
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 16:16:02 2014
** Last update dim. juil. 13 21:36:14 2014 julien thebaud
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"parse.h"
#include	"utils.h"

bool		parse_delay(t_zappy *s, int argc, char **argv, int *flags)
{
  (void)argc;
  (void)argv;
  (*flags) += FLAGS_T;
  if (!is_digit(optarg))
    {
      fprintf(stderr, "Argument of -t must be a number.\n");
      return (false);
    }
  s->delay = atoi(optarg);
  if (s->delay < 1)
    {
      fprintf(stderr, "Argument of -t must be a positif number.\n");
      return (false);
    }
  return (true);
}

bool		parse_nb_clients(t_zappy *s, int argc, char **argv, int *flags)
{
  (void)argc;
  (void)argv;
  (*flags) += FLAGS_C;
  if (!is_digit(optarg))
    {
      fprintf(stderr, "Argument of -c must be a number.\n");
      return (false);
    }
  s->nbClients = atoi(optarg);
  if (s->nbClients < 1 || s->nbClients > 1000000)
    {
      fprintf(stderr, "Argument of -c must be a positif number.\n");
      return (false);
    }
  return (true);
}
