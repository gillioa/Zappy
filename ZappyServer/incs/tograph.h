
#ifndef TO_GRAPH_H
#define TO_GRAPH_H

#include <stdbool.h>
#include "broadcast.h"

#define IGNORE(x) ((void)x)

/* Minimal buffer is 512 */
#ifdef SIZE_BUFF
 #if SIZE_BUFF < 512
   #undef SIZE_BUFF
   #define SIZE_BUFF 512
 #endif
#endif

#ifndef SIZE_BUFF
  #define SIZE_BUFF 512
#endif


char *tograph_msz(t_zappy *z);
char *tograph_tna(t_zappy *z);
char *tograph_sbp(t_zappy *z);
char *tograph_suc(t_zappy *z);
char *tograph_pbc(t_zappy *z);
char *tograph_bct(t_zappy *z);

char *tograph_send_map(t_zappy *z);

char *tograph_pnw(t_zappy *z);
char *tograph_pdi(t_zappy *z);
char *tograph_enw(t_zappy *z);
char *tograph_pex(t_zappy *z);

char *tograph_pdr(t_zappy *z);
char *tograph_pgt(t_zappy *z);

char *tograph_plv(t_zappy *z);
char *tograph_sgt(t_zappy *z);
char *tograph_ppo(t_zappy *z);

char *tograph_welcome_msg(t_zappy *z);

char *tograph_smg(t_zappy *z);
char *tograph_seg(t_zappy *z);

char *tograph_pfk(t_zappy *z);
char *tograph_eht(t_zappy *z);
char *tograph_edi(t_zappy *z);
char *tograph_ebo(t_zappy *z);

char *tograph_pie(t_zappy *z);

char *tograph_pic(t_zappy *z);

char *tograph_pin(t_zappy *z);

char  *concatList(t_list *l);

int   getPlayerId(t_clientIA *player);

#endif
