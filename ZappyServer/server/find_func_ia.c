/*
** find_func_ia.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 15:50:18 2014 courtu_r
** Last update Sun Jul 13 15:50:19 2014 courtu_r
*/

#include	<string.h>
#include	"zappy.h"

/*
** Be careful same order like in clients.h
*/
t_cmd_ia	find_cmd_ia(const char *cmd)
{
  static char *tab_cmd[NB_FUNC_IA + 1] = {
    "avance",
    "droite",
    "gauche",
    "voir",
    "inventaire",
    "prend",
    "pose",
    "expulse",
    "broadcast",
    "incantation",
    "fork",
    "connect_nbr"
  };
  int		i;

  i = -1;
  while (++i < NB_FUNC_IA)
    if (strncmp(cmd, tab_cmd[i], strlen(tab_cmd[i])) == 0)
      return (i);
  return (-1);
}
