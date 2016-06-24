#ifndef _EGG_H_
# define _EGG_H_

#include	"team.h"

typedef unsigned int	uint;
typedef struct s_zappy t_zappy;

typedef struct s_egg
{
  double	tick;
  bool		active;
  unsigned int	id;
  unsigned int	x;
  unsigned int  y;
  t_team	*team;
  t_clientIA *player;
} t_egg;

int	hatch_egg(t_egg *, t_zappy *);
t_egg	*alloc_egg(uint id, t_clientIA *client);

#endif
