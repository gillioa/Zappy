/*
** inventory.h for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ZappyTitou/map
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Mon Jun 23 14:10:36 2014 courtu_r
** Last update Sat Jul 12 15:39:47 2014 courtu_r
*/

#ifndef INVENTORY_H__
# define INVENTORY_H__

typedef struct s_egg	t_egg;
typedef struct s_client_ia t_clientIA;
typedef struct s_zappy t_zappy;

/*Variable defines*/

#define MAX_RESOURCES  5
#define MIN_RESOURCES  1

typedef unsigned int Uint;

typedef enum   resource
  {
    Food,
    Linemate,
    Deraumere,
    Sibur,
    Mendiane,
    Phiras,
    Thystame
  }e_resource;

typedef struct s_inventory
{
  unsigned int	content[7];
}t_inventory;

/*Prototypes for files using inventory.c*/
char		*get_inventory(t_inventory *);

t_inventory	*random_init(t_inventory *inventory);
t_inventory 	*init_inventory(t_inventory *);			// If t_inventory is NULL, will be allocated.

int		get_length(t_inventory *);
int		get_pow(int);
int		add_resource(e_resource, Uint, t_inventory *);	// Returns zero on success
int		del_resource(e_resource, Uint, t_inventory *);	// returns 1 in case of error.
int		decrement_food(t_clientIA *, t_inventory *, t_zappy *, t_egg *);
int		get_nb_resource(e_resource, t_inventory *);

void		print_inventory(t_inventory *);
void		new_client_spawn_food(t_zappy *);
void		timer_spawn_food(t_zappy *);

#endif /*INVENTORY*/
