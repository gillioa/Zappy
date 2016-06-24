/*
** vectors.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
** 
** Made by courtu_r
** Login   <courtu_r@epitech.net>
** 
** Started on  Sat Jul 12 13:06:39 2014 courtu_r
** Last update Sun Jul 13 19:36:23 2014 courtu_r
*/

#include	<math.h>
#include	<string.h>
#include	"zappy.h"

int	get_correct_num(double);
double	scal_prod(double *, double *, bool);
double	*get_shortest_vector(t_clientIA *, t_clientIA *, t_zappy *);
int	my_strlen(char *);
char	*get_param(char *);

double	*get_unit_vector(double x, double y)
{
  double	*vec;

  if (!(vec = malloc(sizeof(*vec) * 2)))
    return (NULL);
  vec[0] = x;
  vec[1] = y;
  return (vec);
}

double	**init_vectors()
{
  double	**result;
  int	cnt;

  if (!(result = malloc(sizeof(*result) * 5)))
    return (NULL);
  result[Up] = get_unit_vector(0.0, -1.0);
  result[Down] = get_unit_vector(0.0, 1.0);
  result[Left] = get_unit_vector(-1.0, 0.0);
  result[Right] = get_unit_vector(1.0, 0.0);
  result[4] = NULL;
  cnt = -1;
  while (result[++cnt]);
  if (cnt != 4)
    return (NULL);
  return (result);
}

double	*get_vector(double x, double y, double origx, double origy)
{
  double	*vec;

  if (!(vec = malloc(sizeof(*vec) * 2)))
    return (NULL);
  vec[0] = origx - x;
  vec[1] = origy - y;
  return (vec);
}

double	*normalize_vec(double *vec_to_norm)
{
  double	*vec;

  if (!(vec = malloc(sizeof(*vec) * 2)))
    return (NULL);
  vec[0] = vec_to_norm[0] * vec_to_norm[0];
  vec[1] = vec_to_norm[1] * vec_to_norm[1];
  return (vec);
}
