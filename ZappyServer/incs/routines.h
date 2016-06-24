#ifndef _ROUTINES_H_
# define _ROUTINES_H_

t_node	*routine_clientIA(t_zappy *s, t_node *node, t_type type, int *ret);
t_node	*routine_connexion(t_zappy *s, t_node *node, t_type type, int *ret);
t_node	*routine_clientGUI(t_zappy *s, t_node *node, t_type type, int *ret);
t_node	*routine_egg(t_zappy *s, t_node *node, t_type type, int *ret);
t_node	*routine_write_answerGUI(t_list *list, t_node *, t_type type, int *);
int	set_big_write(t_zappy *s, t_node *node, t_type t, int *ret);

#endif
