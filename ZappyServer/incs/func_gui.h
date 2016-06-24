#ifndef _FUNC_GUI_H_
# define _FUNC_GUI_H_

#include	<stdio.h>
#include	"zappy.h"

typedef struct s_client_gui t_clientGUI;

int	bct(t_zappy *server, t_clientGUI *client, char *cmd);
int	mct(t_zappy *server, t_clientGUI *client, char *cmd);
int	msz(t_zappy *server, t_clientGUI *client, char *cmd);
int	pin(t_zappy *server, t_clientGUI *client, char *cmd);
int	plv(t_zappy *server, t_clientGUI *client, char *cmd);
int	ppo(t_zappy *server, t_clientGUI *client, char *cmd);
int	sgt(t_zappy *server, t_clientGUI *client, char *cmd);
int	sst(t_zappy *server, t_clientGUI *client, char *cmd);
int	tna(t_zappy *server, t_clientGUI *client, char *cmd);

#endif
