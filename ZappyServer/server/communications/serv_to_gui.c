/*
** serv_to_gui.c for communications in /home/titouan/Dropbox/Bomberman/blowshitup/ServerZappy/server/communications
**
** Made by Titouan Creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Jul 13 13:18:37 2014 Titouan Creach
** Last update Sun Jul 13 14:17:43 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tograph.h"
#include "broadcast.h"
#include "list.h"

int getPlayerId(t_clientIA *player)
{
  return (player->id);
}

void writeClient(char *buffer, t_node *clientIA, t_clientIA *incanter,
    t_list *l)
{
  while (clientIA != NULL)
  {
    if ((((t_clientIA*)clientIA->data) != incanter))
    {
      snprintf(buffer, SIZE_BUFF, " %d",
          getPlayerId(((t_clientIA*)clientIA->data)));
      put_in_list(l, strdup(buffer));
    }
    clientIA = (t_node*)clientIA->next;
  }
  put_in_list(l, strdup("\n"));
}

/*
 ** currentRessource = t_incantation_for_players
 */
char *tograph_pic(t_zappy *z)
{
  char    buffer[SIZE_BUFF];
  t_list  *l;
  t_node  *clientIA;
  t_clientIA  *incanter;

  l = create_list(CHAR);
  clientIA  = ((t_incantation_for_players*)z->currentRessource)
    ->listPlayer->head;
  incanter = ((t_incantation_for_players*)z->currentRessource)->incanter;
  snprintf(buffer, SIZE_BUFF, "pic %u %u %d %d",
      ((t_incantation_for_players*)z->currentRessource)->ncase->pos_x,
      ((t_incantation_for_players*)z->currentRessource)->ncase->pos_y,
      incanter->level,
      getPlayerId(incanter));
  put_in_list(l, strdup(buffer));
  writeClient(buffer, clientIA, incanter, l);
  return (concatList(l));
}

/*
** currentRessource must be a s_clientIA
*/
char *tograph_pin(t_zappy *z)
{
  char buffer[SIZE_BUFF];
  t_clientIA *player;

  player = (t_clientIA*)z->currentRessource;
  snprintf(buffer, SIZE_BUFF, "pin %d %u %u %u %u %u %u %u %u %u\n",
      getPlayerId(player),
      player->x,
      player->y,
      player->inventory->content[0] / 126,
      player->inventory->content[1],
      player->inventory->content[2],
      player->inventory->content[3],
      player->inventory->content[4],
      player->inventory->content[5],
      player->inventory->content[6]);
  return (strdup(buffer));
}
