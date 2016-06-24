/*
** proto.h for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sun Jul 13 16:30:47 2014 courtu_r
** Last update Sun Jul 13 19:37:18 2014 courtu_r
*/

#include "broadcast.h"

#ifndef PROTO_H__
# define PROTO_H__

void	set_end_game(t_zappy *, t_clientIA *);
void	write_level_up(t_zappy *, t_clientIA *);
void	init_int_var_left_right(int *, int *, int *);
void	f2_cor_up_down(int *, t_clientIA *, t_zappy *);
void	f3_cor_up_down(int *, t_clientIA *, t_zappy *, int);
void	init_pos_player_left_right(int *, int *, t_clientIA *);
void	looping_left_right(int *, int *, int *);
void	cor_saw_left_right(t_clientIA *, int *, int, t_zappy *);
void	f_cor_saw_left_right(t_clientIA *, int *, t_zappy *);

bool	place_player(t_clientIA *, t_map *);
bool	add_player_to_pos(t_clientIA *, t_map *, Uint, Uint);
void	remove_player_from_pos(t_clientIA *, t_map *, Uint, Uint);

int	my_strlen(char *);
int	count_nb_players(t_list *);
int	cnt_nb_resources(t_inventory *);
int	get_ressources_to_sub(int);
int	get_nb_cases(int);
int	f_cor_up_down(int *, int *, char **);
int	mid_loop_left_right(int *, int *, char **);

char	*add_players(int, char *, t_zappy *);
char	*get_up_down(t_zappy *, char *, t_clientIA *);
char	*serialize_case(t_case *, char *, t_zappy *);

t_egg	*alloc_egg(uint, t_clientIA *);

#endif /*PROTO_H__*/
