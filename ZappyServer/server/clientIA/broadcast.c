/*
** broadcast.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 12:47:25 2014 courtu_r
** Last update Sun Jul 13 18:37:02 2014 courtu_r
*/

#include	<math.h>
#include	<string.h>
#include	"zappy.h"

double	*get_unit_vector(double, double);
double	**init_vectors();
double	*get_vector(double, double, double, double);
double	*normalize_vec(double *);
int	get_correct_num(double);
double	scal_prod(double *, double *, bool);
double	*get_shortest_vector(t_clientIA *, t_clientIA *, t_zappy *);
int	my_strlen(char *);
char	*get_param(char *);
double	get_sign(double *, double *);

int	get_case(t_clientIA *send, t_clientIA *recv, double **vectors,
		 t_zappy *server)
{
  double		*vec_dist;
  double		*vec_comp;
  double	res;
  double	scalar_prod;
  double	norm_scal_prod;
  double	s;

  vec_dist = get_shortest_vector(recv, send, server);
  vec_comp = vectors[recv->direction];
  s = get_sign(vec_dist, vec_comp);
  scalar_prod = (double)scal_prod(vec_dist, vec_comp, false);
  if (!vec_dist || !vec_comp)
    return (-1);
  norm_scal_prod = (double)scal_prod(vec_dist, vec_comp, true);
  res = scalar_prod / norm_scal_prod;
  free(vec_dist);
  free(vectors[Up]);
  free(vectors[Down]);
  free(vectors[Left]);
  free(vectors[Right]);
  free(vectors);
  return (get_correct_num((s * acos(res)) * (180.0 / M_PI)));
}

char	*create_broadcast_msg(char *msg, int dir)
{
  char	*str;

  if (!(str = malloc(sizeof(*str) * (my_strlen(msg) + 1 + 12))))
    return (NULL);
  sprintf(str, "message %d,%s\n", dir, msg);
  return (str);
}

void	call_back_broadcast(t_zappy *server, t_clientIA *client)
{
  t_node	*node;
  t_clientIA	*other;
  int		ret;

  node = server->listIA->head;
  while (node)
    {
      other = (t_clientIA *)(node->data);
      if (other != client)
	{
	  if (other->x == client->x && other->y == client->y)
	    ret = 0;
	  else
	    ret = get_case(client, other, init_vectors(), server);
	  other->instant_write = create_broadcast_msg(client->broadcast->msg, ret);
	}
      node = node->next;
    }
  server->currentRessource = client->broadcast;
  put_in_list(server->listWrite, create_gui_ans(tograph_pbc(server),
						client->lastAction));
  free(client->broadcast->msg);
  free(client->broadcast);
  client->broadcast = NULL;
}

t_broadcast	*create_broadcast(char *msg, int num)
{
  t_broadcast	*broadcast;

  if (!(broadcast = malloc(sizeof(*broadcast))))
    return (NULL);
  broadcast->msg = strdup(msg);
  free(msg);
  if (broadcast->msg == NULL)
    return (NULL);
  broadcast->noPlayer = num;
  return (broadcast);
}

int	broadcast(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	 frequency;

  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  client->broadcast = create_broadcast(get_param(cmd), client->id);
  if (client->broadcast)
    {
      client->write = true;
      copy_in_buff("ok\n", client->buff_write);
    }
  else
    client->error = true;
  return (0);
}
