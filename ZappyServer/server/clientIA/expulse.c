/*
** expulse.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 13:15:41 2014 courtu_r
** Last update Sun Jul 13 16:34:46 2014 courtu_r
*/

#include	"broadcast.h"

void	init_begin(t_zappy *, t_clientIA *);
int	set_all(t_zappy *, t_clientIA *, t_node *);
int	call_ppo(t_zappy *, t_clientIA *);

int	*init_directions(int *directions)
{
  if ((directions = malloc(sizeof(*directions) * 4)) == NULL)
    return (NULL);
  (directions)[Up] = 1;
  (directions)[Left] = 3;
  (directions)[Right] = 7;
  (directions)[Down] = 5;
  return (directions);
}

char	*get_string(int dir)
{
  int	len;
  char	*ans;

  len = get_pow(dir);
  if ((ans = malloc(sizeof(*ans) * (len + 2 + 14))) == NULL)
    return (NULL);
  sprintf(ans, "deplacement : %d\n", dir);
  return (ans);
}

int	get_expulse_direction(t_clientIA *expulsed, t_clientIA *player,
			      t_zappy *server)
{
  Uint	tmpx;
  Uint	tmpy;
  int	cnt;
  int	dir;

  dir = expulsed->direction;
  cnt = 0;
  while (cnt < 4)
    {
      tmpx = correct_x(expulsed->x + expulsed->x_moves[get_left(dir)], server);
      tmpy = correct_y(expulsed->y + expulsed->y_moves[get_left(dir)], server);
      if (tmpx == player->x && tmpy == player->y)
	return (dir);
      cnt += 1;
    }
  return (dir);
}

char	*get_ans(t_clientIA *expulsed, t_clientIA *player,
		 t_zappy *server)
{
  int	*directions;
  int	dir;

  directions = NULL;
  if ((directions = init_directions(directions)) == NULL)
    return (NULL);
  dir = get_expulse_direction(expulsed, player, server);
  printf("Player (expulsing) : x = %d\ty = %d\tdir = %d\n", player->x,
	 player->y, player->direction);
  printf("Player (expulsed) : x = %d\ty = %d\tdir = %d\n", expulsed->x,
	 expulsed->y, expulsed->direction);
  printf("Expulsion dir is : %d\n", dir);
  free(directions);
  return (get_string(dir));
}

int	expulse(t_zappy *server, t_clientIA *client, char *cmd)
{
  t_node	*node;
  double	frequency;

  (void)cmd;
  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  node = server->map->map[correct_y(client->y,
				    server)][correct_x(client->x,
						       server)]->players->head;
  server->currentRessource = client;
  if (!put_in_list(server->listWrite, create_gui_ans(tograph_pex(server),
						     client->lastAction)))
    return (1);
  if (set_all(server, client, node))
    return (1);
  client->write = true;
  copy_in_buff("ok\n", client->buff_write);
  return (0);
}
