#ifndef _FUNC_IA_H_
# define _FUNC_IA_H_

#include	<stdio.h>
#include	"clients.h"
#include	"zappy.h"

int	see(t_zappy *server, t_clientIA *client, char *cmd);
int	left(t_zappy *server, t_clientIA *client, char *cmd);
int	move(t_zappy *server, t_clientIA *client, char *cmd);
int	_fork(t_zappy *server, t_clientIA *client, char *cmd);
int	right(t_zappy *server, t_clientIA *client, char *cmd);
int	put_obj(t_zappy *server, t_clientIA *client, char *cmd);
int	expulse(t_zappy *server, t_clientIA *client, char *cmd);
int	take_obj(t_zappy *server, t_clientIA *client, char *cmd);
int	broadcast(t_zappy *server, t_clientIA *client, char *cmd);
int	inventory(t_zappy *server, t_clientIA *client, char *cmd);
int	connect_nbr(t_zappy *server, t_clientIA *client, char *cmd);
int	incantation(t_zappy *server, t_clientIA *client, char *cmd);

#endif
