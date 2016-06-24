#ifndef	_PARSE_H_
# define _PARSE_H_

#include	<stdbool.h>
#include	"zappy.h"

#define		KARSET_OPT	"pxynct"
#define		NB_OPT		(strlen(KARSET_OPT))

#define		FLAGS_P		1
#define		FLAGS_X		2
#define		FLAGS_Y		4
#define		FLAGS_N		8
#define		FLAGS_C		16
#define		FLAGS_T		32

int		init_server(t_zappy *server);
int		fill_opt(int argc, char **argv, t_zappy *server);
bool		parse_port(t_zappy *, int, char **, int *);
bool		parse_width(t_zappy *, int, char **, int *);
bool		parse_height(t_zappy *, int, char **, int *);
bool		parse_name_team(t_zappy *, int, char **, int *);
bool		parse_nb_clients(t_zappy *, int, char **, int *);
bool		parse_delay(t_zappy *, int, char **, int*);

#endif
