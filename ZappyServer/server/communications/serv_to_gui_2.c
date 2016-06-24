/*
** serv_to_gui_2.c for communications in /home/titouan/Dropbox/Bomberman/blowshitup/ServerZappy/server/communications
**
** Made by Titouan Creach
** Login   <creach_a@epitech.net>
**
** Started on  Sun Jul 13 13:19:37 2014 Titouan Creach
** Last update Sun Jul 13 13:19:37 2014 Titouan Creach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tograph.h"
#include "broadcast.h"
#include "list.h"

/*
** Concat char* list into a single char*
** /!\ this function FREE the list
*/
char  *concatList(t_list *l)
{
  size_t		size;
  char			*copy_addr;
  char			*content;
  struct s_node   	*it;

  size = 0;
  content = NULL;
  it = l->head;
  while (it != NULL)
  {
    size += strlen((char*)it->data);
    content = realloc(content, sizeof(char) * (size + 1));
    copy_addr = content + size - strlen((char*)it->data);
    strcpy(copy_addr, (char*)it->data);
    it = it->next;
  }
  release_list(l);
  return (content);
}

char	*tograph_welcome_msg(t_zappy *z)
{
  t_list *list;
  t_node *clientIA;
  t_node *egg;

  list = create_list(CHAR);
  put_in_list(list, tograph_msz(z));
  put_in_list(list, tograph_sgt(z));
  put_in_list(list, tograph_send_map(z));
  put_in_list(list, tograph_tna(z));
  clientIA = z->listIA->head;
  egg = z->listEGG->head;
  while (clientIA != NULL)
  {
    z->currentRessource = ((t_clientIA*)clientIA->data);
    put_in_list(list, tograph_pnw(z));
    clientIA = (t_node*)clientIA->next;
  }
  while (egg != NULL)
  {
    z->currentRessource = ((t_egg*)egg->data);
    put_in_list(list, tograph_enw(z));
    egg = (t_node*)egg->next;
  }
  return (concatList(list));
}

/*
** currentRessource == OSEF
*/
char	*tograph_msz(t_zappy *z)
{
  char		buffer[SIZE_BUFF];
  t_map		*map;

  map = z->map;
  snprintf(buffer, SIZE_BUFF, "msz %u %u\n",
    map->width,
    map->height);
  return strdup(buffer);
}

/*
 ** Don't care about currentRessource
 */
char *tograph_tna(t_zappy *z)
{
  t_list 		*buffList;
  char 			buffer[SIZE_BUFF];
  t_node 		*teams;

  buffList = create_list(CHAR);
  teams = (t_node*)z->listTeam->head;
  while (teams != NULL)
  {
    bzero(buffer, SIZE_BUFF);
    snprintf(buffer, SIZE_BUFF, "tna %s\n", ((t_team*)teams->data)->name);
    put_in_list(buffList, strdup(buffer));
    teams = (t_node*)teams->next;
  }
  return (concatList(buffList));
}

/*
 ** Don't care about currentRessource
 */
char *tograph_sbp(t_zappy *z)
{
  IGNORE(z);
  return (strdup("sbp\n"));
}
