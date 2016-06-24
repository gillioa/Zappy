/*
** is_digit.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/utils
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 16:07:31 2014 
** Last update Sun Jul 13 16:07:33 2014 
*/

#include	<stdbool.h>

bool	is_digit(char *str)
{
  int		i;

  i = -1;
  if ((!str) || str[0] == '\0')
    return (false);
  while (str[++i])
    if (str[i] < '0' || str[i] > '9')
      return (false);
  return (true);
}
