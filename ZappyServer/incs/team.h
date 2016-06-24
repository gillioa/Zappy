#ifndef _TEAM_H
# define _TEAM_H

typedef struct s_team
{
  char		name[32];
  unsigned int	nb_slots_max;
  unsigned int	length;
  unsigned int	nbplayers;
} t_team;

#endif
