/*
** put_obj.c for Zappy in /home/courtu_r/BOMBERMAN/thirdvers/blowshitup/ServerZappy
**
** Made by courtu_r
** Login   <courtu_r@epitech.net>
**
** Started on  Sat Jul 12 12:27:27 2014 courtu_r
** Last update Sun Jul 13 19:47:13 2014 courtu_r
*/

#include	<string.h>
#include	"zappy.h"
#include	"broadcast.h"

int	send_case_inventory(t_zappy *, t_clientIA *, t_case *);

t_ressourcePlayer	*set_object(t_zappy *server, t_clientIA *client,
				    int resource)
{
  t_ressourcePlayer	*to_send;

  if (!(to_send = malloc(sizeof(*to_send))))
    return (NULL);
  to_send->clientIA = client;
  to_send->noRessource = resource;
  server->currentRessource = to_send;
  return (to_send);
}

char	*get_param(char *str)
{
  int	n;
  char	*new;
  int	size;

  n = 0;
  while (str[n] && str[n] != ' ' && str[n] != '\t')
    n += 1;
  while (str[n] && (str[n] == ' ' || str[n] == '\t'))
    n += 1;
  size = strlen(str) - n;
  if ((new = malloc(sizeof(*new) * (size + 1))) == NULL)
    return (NULL);
  size = 0;
  while (str[n])
    {
      if (str[n] != '\n')
	{
	  new[size] = str[n];
	  size += 1;
	}
      n += 1;
    }
  new[size] = 0;
  return (new);
}

int	pose_information(t_zappy *server, t_clientIA *client, int i,
			 t_case *pos)
{
  char	*str;

  if (!set_object(server, client, i))
    return (1);
  if (!(str = tograph_pdr(server)))
    return (1);
  free(server->currentRessource);
  if (!put_in_list(server->listWrite, create_gui_ans(str, client->lastAction)))
    return (1);
  if (send_case_inventory(server, client, pos))
    return (1);
  return (0);
}

int	put_obj(t_zappy *server, t_clientIA *client, char *cmd)
{
  double	 frequency;
  char		*resource;
  int		i = 0;
  t_case	*pos;

  pos = server->map->map[client->y][client->x];
  frequency = ((double)7.0f / server->delay);
  client->lastAction = get_tick(frequency);
  resource = get_param(cmd);
  while (i < 7 && strcmp(resource, server->resources[i]))
    i += 1;
  if (i > 6 || get_nb_resource(i, client->inventory) <= 0)
    {
      client->error = true;
      return (1);
    }
  add_resource(i, 1, pos->inventory);
  del_resource(i, 1, client->inventory);
  if (pose_information(server, client, i, pos))
    return (1);
  copy_in_buff("ok\n", client->buff_write);
  client->write = true;
  return (0);
}
