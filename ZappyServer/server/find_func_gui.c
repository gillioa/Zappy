/*
** find_func_gui.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 15:50:47 2014 courtu_r
** Last update Sun Jul 13 15:50:48 2014 courtu_r
*/

#include	<string.h>
#include	"zappy.h"

/*
** Be careful same order like in clients.h
*/
t_cmd_gui	find_cmd_gui(const char *cmd)
{
  static char *tab_cmd[NB_FUNC_GUI + 1] = {
    "msz",
    "bct",
    "mct",
    "tna",
    "ppo",
    "plv",
    "pin",
    "sgt",
    "sst"
  };
  int		i;

  i = -1;
  while (++i < NB_FUNC_GUI)
    if (strncmp(cmd, tab_cmd[i], strlen(tab_cmd[i])) == 0)
      return (i);
  return (-1);
}
