/*
** serv_to_gui_3.c for communications in /home/titouan/Dropbox/Bomberman/blowshitup/ServerZappy/server/communications
**
** Made by Titouan Creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Jul 13 13:19:57 2014 Titouan Creach
** Last update Sun Jul 13 13:19:57 2014 Titouan Creach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tograph.h"
#include "broadcast.h"
#include "list.h"

/*
 ** Don't care about currentRessource
 */
char *tograph_suc(t_zappy *z)
{
  IGNORE(z);
  return (strdup("suc\n"));
}

/*
 ** currentRessource must be a t_broadcast*
 */
char *tograph_pbc(t_zappy *z)
{
  t_broadcast *broadcast;
  char buffer[SIZE_BUFF];

  broadcast = (t_broadcast*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "pbc %u %s\n",
			broadcast->noPlayer,
			broadcast->msg);
  return (strdup(buffer));
}

/*
 ** currentRessource must be a t_case*
 */
char *tograph_bct(t_zappy *z)
{
  char buffer[SIZE_BUFF];
  t_case *ncase;

  ncase = (t_case*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "bct %d %d %u %u %u %u %u %u %u\n",
      ncase->pos_x,
      ncase->pos_y,
      ncase->inventory->content[0] / 126,
      ncase->inventory->content[1],
      ncase->inventory->content[2],
      ncase->inventory->content[3],
      ncase->inventory->content[4],
      ncase->inventory->content[5],
      ncase->inventory->content[6]);
  return (strdup(buffer));
}

/* dont care about currentRessource */
char *tograph_send_map(t_zappy *z)
{
  t_map 	*map;
  t_list 	*l;
  Uint 		i;
  Uint 		j;

  l = create_list(CHAR);
  map = z->map;
  i = 0;
  j = 0;
  while (i < map->height)
  {
    while (j < map->width)
    {
      z->currentRessource = map->map[i][j];
      put_in_list(l, tograph_bct(z));
      ++j;
    }
    j = 0;
    ++i;
  }
  return (concatList(l));
}

/*
 ** currentRessource must be a t_clientIA*
 */
char *tograph_pnw(t_zappy *z)
{
  t_clientIA *newPlayer;
  char buffer[SIZE_BUFF];

  newPlayer = (t_clientIA*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "pnw %d %d %d %d %u %s\n",
      getPlayerId(newPlayer),
      newPlayer->x,
      newPlayer->y,
      newPlayer->direction + 1,
      newPlayer->level,
      newPlayer->team->name);
  return strdup(buffer);
}
