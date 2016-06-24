/*
** fill_option.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/init
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 16:15:03 2014
** Last update dim. juil. 13 19:50:19 2014 julien thebaud
*/

#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	"parse.h"

static int	get_opt(char opt);
static int	print_usage(char *name);
static int	check_opt(int opt_flags, char *name);
static void	init_func_opt(bool (*ptr[NB_OPT])());

int		fill_opt(int argc, char **argv, t_zappy *server)
{
  int		c;
  int		call;
  int		opt_flags;
  bool		(*func_opt[NB_OPT])(t_zappy *, int, char **, int *);

  opt_flags = 0;
  if ((argc == 2) && (strncmp(argv[1], "-h", 2) == 0))
    return (print_usage(argv[0]));
  init_func_opt(func_opt);
  server->port = 4242;
  server->delay = 100;
  while ((c = getopt(argc, argv, "p:x:y:n:c:t:")) != -1)
    {
      if (c == '?')
	return (fprintf(stderr, "%s: -h for usage.\n", argv[0]));
       else
	{
	  call = get_opt(c);
	  if (call > -1 && call < ((int)NB_OPT))
	    if (!((*func_opt[call])(server, argc, argv, &opt_flags)))
	      return (1);
	}
    }
  return (check_opt(opt_flags, argv[0]));
}

static int	get_opt(char opt)
{
  int		i;

  i = -1;
  while (KARSET_OPT[++i])
    if (KARSET_OPT[i] == opt)
      return (i);
  return (-1);
}

static int	print_usage(char *name)
{
  fprintf(stderr, "Usage: %s:\n", name);
  fprintf(stderr, "[-p port]\n");
  fprintf(stderr, "-x width\n");
  fprintf(stderr, "-y height\n");
  fprintf(stderr, "-n team1 [team2 [...]]\n");
  fprintf(stderr, "-c max player per team\n");
  fprintf(stderr, "[-t time delay]\n");
  return (1);
}

static int	check_opt(int opt_flags, char *name)
{
  int		ret;

  ret = 0;
  if (!(opt_flags & FLAGS_X))
    ret = fprintf(stderr, "Option -x width is required.\n");
  if (!(opt_flags & FLAGS_Y))
    ret = fprintf(stderr, "Option -y height is required.\n");
  if (!(opt_flags & FLAGS_N))
    ret = fprintf(stderr, "Option -n name_of_team(s) is required.\n");
  if (!(opt_flags & FLAGS_C))
    ret = fprintf(stderr, "Option -c nb players per team is required.\n");
  if (ret > 0)
    return (fprintf(stderr, "%s: -h for usage.\n", name));
  return (0);
}

static void	init_func_opt(bool (*ptr[NB_OPT])())
{
  ptr[0] = &parse_port;
  ptr[1] = &parse_width;
  ptr[2] = &parse_height;
  ptr[3] = &parse_name_team;
  ptr[4] = &parse_nb_clients;
  ptr[5] = &parse_delay;
}
