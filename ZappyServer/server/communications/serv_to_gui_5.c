/*
** serv_to_gui_5.c for communications in /home/titouan/Dropbox/Bomberman/blowshitup/ServerZappy/server/communications
**
** Made by Titouan Creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Jul 13 13:20:05 2014 Titouan Creach
** Last update Sun Jul 13 13:20:05 2014 Titouan Creach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tograph.h"
#include "broadcast.h"
#include "list.h"

/*
** currentRessource must be a t_clientIA*)
*/
char *tograph_plv(t_zappy *z)
{
  char        buffer[SIZE_BUFF];
  t_clientIA  *player;

  player = (t_clientIA*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "plv %d %u\n",
      getPlayerId(player),
      player->level);
  return strdup(buffer);
}

/*
** don't care about currentRessource
*/
char *tograph_sgt(t_zappy *z)
{
  char buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "sgt %d\n", z->delay);
  return strdup(buffer);
}

/*
** currentRessource must point to a struct s_clientIA*
*/
char *tograph_ppo(t_zappy *z)
{
  char buffer[SIZE_BUFF];
  t_clientIA *player;

  player = (t_clientIA*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "ppo %d %d %d %d\n",
      getPlayerId(player),
      player->x,
      player->y,
      player->direction + 1);
  return (strdup(buffer));
}

/*
** currentRessource must point to a char*
*/
char *tograph_smg(t_zappy *z)
{
  char buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "smg %s\n", (char*)z->currentRessource);
  return strdup(buffer);
}

/*
** currentRessource must point to the winner's team
*/
char *tograph_seg(t_zappy *z)
{
  char buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "seg %s\n",
			((t_team*)z->currentRessource)->name);
  return strdup(buffer);
}
