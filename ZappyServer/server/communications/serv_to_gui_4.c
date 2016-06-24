/*
** serv_to_gui_4.c for communications in /home/titouan/Dropbox/Bomberman/blowshitup/ServerZappy/server/communications
**
** Made by Titouan Creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Jul 13 13:20:01 2014 Titouan Creach
** Last update Sun Jul 13 20:51:38 2014 courtu_r
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tograph.h"
#include "broadcast.h"
#include "list.h"

/*
** currentRessource == t_egg*
*/
char *tograph_enw(t_zappy *z)
{
  char    buffer[SIZE_BUFF];
  t_egg   *egg;

  egg = (t_egg*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "enw %u %d %d %d\n",
	   egg->id,
      getPlayerId(egg->player),
      egg->x,
      egg->y);
  return (strdup(buffer));
}

/*
** currentRessource must be a t_clientIA*
*/
char *tograph_pdi(t_zappy *z)
{
  t_clientIA *diedPlayer;
  char buffer[SIZE_BUFF];

  diedPlayer = (t_clientIA*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "pdi %d\n",
      getPlayerId(diedPlayer));
 return strdup(buffer);
}

/*
** currentRessource must be a t_clientIA*
*/
char *tograph_pex(t_zappy *z)
{
  t_clientIA 	*kickedPlayer;
  char 		buffer[SIZE_BUFF];

  kickedPlayer = (t_clientIA*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "pex %d\n",
      getPlayerId(kickedPlayer));
  return strdup(buffer);
}

/*
** currentRessource must be a t_ressourcePlayer*
*/
char *tograph_pdr(t_zappy *z)
{
  char 			buffer[SIZE_BUFF];
  t_ressourcePlayer 	*ressourcePlayer;

  ressourcePlayer = (t_ressourcePlayer*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "pdr %d %d\n",
      getPlayerId(ressourcePlayer->clientIA),
      ressourcePlayer->noRessource);
  return (strdup(buffer));
}

/*
** currentRessource must be a t_ressourcePlayer*
*/
char *tograph_pgt(t_zappy *z)
{
  char              buffer[SIZE_BUFF];
  t_ressourcePlayer *ressourcePlayer;

  ressourcePlayer = (t_ressourcePlayer*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "pgt %d %d\n",
      getPlayerId(ressourcePlayer->clientIA),
      ressourcePlayer->noRessource);
  return strdup(buffer);
}
