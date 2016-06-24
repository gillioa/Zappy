#ifndef BROADCAST_H
#define BROADCAST_H

#include "zappy.h"

typedef struct s_case	t_case;
typedef struct s_map	t_map;

typedef struct s_gui_answer
{
  unsigned int	tick;
  char		*msg;
}t_gui_answer;

typedef struct s_broadcast
{
  unsigned int  noPlayer;
  char          *msg;
}t_broadcast;

typedef struct s_ressourcePlayer
{
  t_clientIA *clientIA;
  int noRessource;
}t_ressourcePlayer;

/*
** Result = 0 || 1
*/
typedef struct s_incantation_ended
{
  t_case *ncase;
  unsigned char result;
}t_incantation_ended;


typedef struct s_incantation_for_players
{

  t_case *ncase; //Sur quelle case l'incantation commence
  t_list *listPlayer; //la liste des players qui sont sur la case
  t_clientIA	*incanter;
  // T'as craque mon pauvre. Tu crois jvais faire un sort?
  // Jte files un t_clientIA * oui.
  //le premier doit etre celui quand lance l'incantation!!

}t_incantation_for_players;

t_gui_answer	*create_gui_ans(char *, unsigned int);

#endif
