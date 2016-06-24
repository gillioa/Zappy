/*
** func_parse.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/init
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 16:15:11 2014
** Last update dim. juil. 13 21:40:20 2014 julien thebaud
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	"parse.h"
#include	"utils.h"

static t_team	*alloc_team(const char *name);

bool		parse_port(t_zappy *s, int argc, char **argv, int *flags)
{
  (void)argc;
  (void)argv;
  (*flags) += FLAGS_P;
  if (!is_digit(optarg))
    {
      fprintf(stderr, "Argument of -p must be a number.\n");
      return (false);
    }
  s->port = atoi(optarg);
  if (s->port < 1 || s->port > 65535)
    {
      fprintf(stderr, "Argument of -p must be a positif number.\n");
      return (false);
    }
  return (true);
}

bool		parse_width(t_zappy *s, int argc, char **argv, int *flags)
{
  (void)argc;
  (void)argv;
  (*flags) += FLAGS_X;
  if (!is_digit(optarg))
    {
      fprintf(stderr, "Argument of -x must be a number.\n");
      return (false);
    }
  s->width = atoi(optarg);
  if (s->width < 1 || s->width > 1000000)
    {
      fprintf(stderr, "Argument of -x must be a positif number.\n");
      return (false);
    }
  return (true);
}

bool		parse_height(t_zappy *s, int argc, char **argv, int *flags)
{
  (void)argc;
  (void)argv;
  (*flags) += FLAGS_Y;
  if (!is_digit(optarg))
    {
      fprintf(stderr, "Argument of -y must be a number.\n");
      return (false);
    }
  s->height = atoi(optarg);
  if (s->height < 1 || s->height > 1000000)
    {
      fprintf(stderr, "Argument of -y must be a positif number.\n");
      return (false);
    }
  return (true);
}

bool		parse_name_team(t_zappy *s, int argc, char **argv, int *flags)
{
  int		index;
  t_team	*team;

  (*flags) += FLAGS_N;
  index = optind - 2;
  while (++index < argc && argv[index][0] != '-')
    {
      if (strlen(argv[index]) < 1)
	{
	  fprintf(stderr, "Invalid length of team name\n");
	  return (false);
	}
      if (!(team = alloc_team(argv[index])))
	return (false);
      team->nb_slots_max = s->nbClients;
      if (!(put_in_list(s->listTeam, team)))
	return (false);
    }
  return (true);
}

static t_team	*alloc_team(const char *name)
{
  t_team	*ret;

  if (!(ret = malloc(sizeof(*ret))))
    return (NULL);
  bzero(ret->name, sizeof(ret->name));
  ret->length = strlen(name);
  ret->nbplayers = 0;
  if (ret->length < sizeof(ret->name))
    strncpy(ret->name, name, ret->length);
  else
    strncpy(ret->name, name, sizeof(ret->name) - 1);
  return (ret);
}
