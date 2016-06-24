#ifndef _CLIENTS_H
# define _CLIENTS_H

#include	<stdbool.h>
#include	"inventory.h"
#include	"list.h"
#include	"team.h"
#include	"zappy.h"
#include	"types.h"
#include	"case.h"
#include	"circular_buffer.h"
#include	"broadcast.h"


typedef struct s_broadcast t_broadcast;

typedef struct s_client_conn
{
  SOCKET	socket;
  bool		welcome;
  bool		write;
  bool		deco;
  t_buff	*buff_read;
} t_conn;

typedef enum	direction
  {
    Up,
    Right,
    Down,
    Left
  }dir;

typedef enum e_cmd_client_ia
{
  UNKNOWN = -1,
  MOVE = 0,
  RIGHT = 1,
  LEFT = 2,
  SEE = 3,
  INVENTORY = 4,
  TAKE_OBJ = 5,
  PUT_OBJ = 6,
  EXPULSE = 7,
  BROADCAST = 8,
  INCANTATION = 9,
  FORK = 10,
  CONNECT_NBR = 11
} t_cmd_ia;

typedef struct s_client_ia t_clientIA;
typedef struct s_zappy	t_zappy;

typedef struct s_client_ia
{
  t_broadcast	*broadcast;
  char		*instant_write;
  char		*incantation;
  bool		call_incantation;
  SOCKET	socket;
  int		old_id;
  int		level;
  int		x_moves[4];
  int		y_moves[4];
  unsigned int	x;
  unsigned int  y;
  unsigned int	id;
  t_buff	*buff_read;
  t_buff	*buff_write;
  t_team	*team;
  char		*big_write;
  bool		error;
  bool		write;
  t_inventory	*inventory;
  dir		direction;
  bool		isDead;
  double	lastAction;
  double	decLife;
  int		(*move[4])(t_zappy *, t_clientIA *);
  unsigned int	nb_recv;
} t_clientIA;

typedef enum e_cmd_client_gui
{
  NONE = -1,
  MSZ = 0,
  BCT = 1,
  MCT = 2,
  TNA = 3,
  PPO = 4,
  PLV = 5,
  PIN = 6,
  SGT = 7,
  SST = 8
} t_cmd_gui;

typedef struct s_client_gui
{
  SOCKET	socket;
  t_buff	*buff_read;
  t_buff	*buff_write;
  bool		error;
  bool		write;
  char		*buff;
  char		*writeConn;
  char		*all_map;
  t_list	*listWrite;
} t_clientGUI;

int	correct_y(int, t_zappy *);
int	correct_x(int, t_zappy *);
int	move_up(t_zappy*, t_clientIA *);
int	move_right(t_zappy*, t_clientIA *);
int	move_down(t_zappy*, t_clientIA *);
int	move_left(t_zappy*, t_clientIA *);
dir	get_right(dir);
dir	get_left(dir);
void	write_incantation(t_zappy *s, t_clientIA *client);
void	write_buffer_ia(t_clientIA *client, char **buff);
void	write_cmd(t_clientIA *client);
void	write_gui(t_zappy *s, t_clientGUI *client);
void    write_error_ia(t_clientIA *client, const char *error);

#endif
