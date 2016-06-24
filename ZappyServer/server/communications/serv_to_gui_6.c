/*
** serv_to_gui_6.c for communications in /home/titouan/Dropbox/Bomberman/blowshitup/ServerZappy/server/communications
**
** Made by Titouan Creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Jul 13 13:21:03 2014 Titouan Creach
** Last update Sun Jul 13 13:21:03 2014 Titouan Creach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tograph.h"
#include "broadcast.h"
#include "list.h"

/*
** currentRessource = t_clientIA
*/
char *tograph_pfk(t_zappy *z)
{
  char buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "pfk %d\n",
      getPlayerId((t_clientIA*)z->currentRessource));
  return strdup(buffer);
}

/*
** currentRessource = t_egg*
*/
char *tograph_eht(t_zappy *z)
{
  char buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "eht %u\n",
      ((t_egg*)z->currentRessource)->id);
  return strdup(buffer);
}

/*
** currentRessource = t_egg*
*/
char *tograph_edi(t_zappy *z)
{
  char buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "edi %u\n",
      ((t_egg*)z->currentRessource)->id);
  return strdup(buffer);
}

/*
** currentRessource = t_egg*
*/
char *tograph_ebo(t_zappy *z)
{
  char buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "ebo %u\n",
      ((t_egg*)z->currentRessource)->id);
  return strdup(buffer);
}

/*
** currentRessource = t_incantation_ended*
*/
char *tograph_pie(t_zappy *z)
{
  char 		buffer[SIZE_BUFF];

  snprintf(buffer, SIZE_BUFF, "pie %u %u %d\n",
      ((t_incantation_ended*)z->currentRessource)->ncase->pos_x,
      ((t_incantation_ended*)z->currentRessource)->ncase->pos_y,
      ((t_incantation_ended*)z->currentRessource)->result);
  return (strdup(buffer));

}

