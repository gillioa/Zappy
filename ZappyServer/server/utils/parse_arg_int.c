/*
** parse_arg_int.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/utils
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 16:07:40 2014
** Last update dim. juil. 13 16:35:41 2014 julien thebaud
*/

#include	<string.h>
#include	<stdlib.h>
#include	"zappy.h"
#include	"utils.h"

static unsigned int	len_first(char *num);
static int 	parse_second(char *cmd, char *arg1, unsigned int *a2);

int		parse_two_int(char *cmd, unsigned int *a1, unsigned int *a2)
{
  char		*arg1;
  char		*arg2;

  arg2 = NULL;
  arg1 = get_param(cmd);
  if (a1)
    {
      *(a1) = atoi(arg1);
      if ((*(a1) == 0) && arg1[0] != '0')
	{
	  free(arg1);
	  return (1);
	}
    }
  if (parse_second(arg2, arg1, a2))
    return (1);
  free_va_arg(2, arg1, arg2);
  return (0);
}

static int 	parse_second(char *arg2, char *arg1, unsigned int *a2)
{
  unsigned int	index;

  index = len_first(arg1);
  if (a2)
    {
      if (index == strlen(arg1))
	{
	  free(arg1);
	  return (1);
	}
      arg2 = get_param(arg1);
      arg1[index] = '\0';
      (*a2) = atoi(arg2);
      if (((*a2) == 0) && arg2[0] != '0')
	{
	  free_va_arg(2, arg1, arg2);
	  return (1);
	}
    }
  return (0);
}

static unsigned int	len_first(char *num)
{
  unsigned int	ret;

  ret = 0;
  while (*(num++))
    {
      if (*(num - 1) < '0' || *(num - 1) > '9')
	return (ret);
      else
	++ret;
    }
  return (ret);
}
