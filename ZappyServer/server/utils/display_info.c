/*
** display_info.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/utils
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 16:07:25 2014 
** Last update Sun Jul 13 16:07:58 2014 
*/

#include	"zappy.h"

const char	*get_color_term(t_color col)
{
  static char	  tab[NB_COLOR_TERM][15] = {
    "\033[01;32m",
    "\033[01;33m",
    "\033[01;31m",
    "\033[01;34m",
    "\033[01;0m"
  };

  return (tab[col]);
}
