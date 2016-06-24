/*
** connect_nbr.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 13:13:05 2014 courtu_r
** Last update sam. juil. 12 19:11:05 2014 julien thebaud
*/

#include	"zappy.h"

int	connect_nbr(t_zappy *server, t_clientIA *client, char *cmd)
{
  int	len;
  int	res;
  char	*ans;

  (void)cmd;
  (void)server;
  res = client->team->nb_slots_max - client->team->nbplayers;
  len = get_pow(res);
  if ((ans = malloc(sizeof(*ans) * (len + 2))) == NULL)
    return (1);
  sprintf(ans, "%d\n", res);
  printf("Ans = [%s]\n", ans);
  client->lastAction = 0.0f;
  copy_in_buff(ans, client->buff_write);
  client->write = true;
  free(ans);
  return (0);
}
