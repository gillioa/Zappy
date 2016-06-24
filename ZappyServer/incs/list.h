#ifndef _LIST_H_
# define _LIST_H_

#include	<stdbool.h>

typedef struct s_zappy t_zappy;

typedef enum e_type
{
  CONN,
  IA,
  GUI,
  TEAM,
  PLAYER,
  CHAR,
  EGG,
  WRITE,
  ANSWER
} t_type;

typedef struct s_node
{
  void			*data;
  struct s_node		*next;
  struct s_node		*prev;
} t_node;

typedef struct s_list
{
  unsigned int	length;
  t_type	type;
  t_node	*head;
  t_node	*end;
} t_list;

int	release_node(t_node *node, t_type type);
t_list	*create_list(t_type type); // Init list avec le type;
t_node	*rm_node(t_list *list, t_node *node); // rm node : params : list courante, node concerne.
bool	put_in_list(t_list *list, void *data); // list et data
t_node	*rm_node(t_list *list, t_node *node);
int	release_list(t_list *list);
int	      iter_routine_next(t_list *list, t_zappy *s,
			 t_node *(*p_func)(t_zappy*, t_node*, t_type, int *));
int	iter(t_list *list, t_zappy *s,
			 int (*p_func)(t_zappy *, t_node *, t_type, int *));
int	iter_list_ret_next(t_list *list, int init,
			   t_node *(*func)(t_list *l, t_node*, t_type, int *));

#endif
