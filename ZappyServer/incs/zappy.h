#ifndef _ZAPPY_H_
# define _ZAPPY_H_

#include	<stdbool.h>
#include	"map.h"
#include	"list.h"
#include	"team.h"
#include	"egg.h"
#include	"types.h"
#include	"inventory.h"
#include	"clients.h"
#include	"tograph.h"
#include	"func_ia.h"
#include	"func_gui.h"
#include	"routines.h"
#include	"circular_buffer.h"

#define HOME_GUI	"GRAPHIC"
#define NB_FUNC_IA	12
#define NB_FUNC_GUI	9
#define	UNIT_TIME	126.0f

typedef struct s_client_conn t_conn;
typedef enum e_cmd_client_ia t_cmd_ia;
typedef enum e_cmd_client_gui t_cmd_gui;

typedef struct s_zappy
{
  int			nb_players[8];
  t_inventory		*incantation_requirements;
  char			*resources[9];
  unsigned int		nbClients;
  unsigned int		width;
  unsigned int		height;
  unsigned int		port;
  int			delay;
  SOCKET		listen;
  t_list		*listConn;
  t_list		*listTeam;
  t_list		*listIA;
  t_list		*listGUI;
  t_list		*listEGG;
  fd_set		readsd;
  fd_set		writesd;
  fd_set		exceptsd;
  TIMEVAL		timeval;
  TIMEVAL		timeActu;
  int			max_sd;
  t_map			*map;
  unsigned int		max_id;
  int			(*ptr_func_ia[NB_FUNC_IA + 1])(t_zappy *s,
						       t_clientIA *c,
						       char *cmd);
  int			(*ptr_func_gui[NB_FUNC_GUI + 1])(t_zappy *s,
							 t_clientGUI *c,
							 char *cmd);
  void			*currentRessource;
  t_list		*listWrite;
  char			*writeCmd;
  char			*writeGui;
  bool			game;
} t_zappy;

void		print_time(void);
double		get_tick(double sec);
char		*_concatList(t_list *l);
void		print_time_param(double);
int		schedule(t_zappy *server);
int		connexion(t_zappy *server);
t_clientGUI	*alloc_clientGUI(SOCKET sd);
int		init_signal(t_zappy *server);
t_cmd_ia	find_cmd_ia(const char *cmd);
const char	*get_color_term(t_color col);
t_cmd_gui	find_cmd_gui(const char *cmd);
int		display_info(t_zappy *server);
bool		is_writed(t_zappy *s, int index);
int		can_write_buffer(t_buff *buff);
void		set_connect_nbr(t_zappy *server);
bool		create_socket_TCP(t_zappy *server);
void		add_socket_to_monitor(t_zappy *server);
int		release_memory(t_zappy *server, int ret);
t_clientIA	*alloc_clientIA(t_team *team, SOCKET sd);
int		print_info(t_color color, const char *str);
void		do_fd_sets(t_zappy *s, t_clientGUI *client);
t_clientIA	*is_in_list_of_ia(t_list *list, t_team *team);
t_team		*is_in_list_of_team(t_list *list, const char *name);
void		send_buffer(t_clientIA *client, const char *buffer);
t_clientIA	*get_clientIA_by_index(t_list *list, unsigned int num);
int		choose_graphic_or_ia(t_zappy *s, t_conn *c, const char *buff);
bool		are_requirements_met(t_zappy *server, t_clientIA *client, bool first_check);
void		*free_va_arg(int, ...);
t_inventory	*init_inventories(t_zappy*);
t_inventory	*get_inventory_to_comp(int, t_zappy*);
t_clientIA	*is_in_list_egg(t_list *l, t_team *t, t_conn *c, t_zappy *s);
void		first_send_ia(t_clientIA *clientIA, t_zappy *s, t_team *team);
void		call_back_broadcast(t_zappy *server, t_clientIA *client);
int		choose_client(t_zappy *server, t_team *team, t_conn *c);
int		create_client_ia(t_zappy *s, t_conn* c, t_team *team);

#endif
