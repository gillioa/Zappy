/*
** init_server.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/init
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 16:15:18 2014
** Last update dim. juil. 13 19:50:39 2014 julien thebaud
*/

#include	<time.h>
#include	<stdlib.h>
#include	"zappy.h"

static void	init_ptr_func_ia(t_zappy *server);
static void	init_ptr_func_gui(t_zappy *server);
static int	init_resource_strings(t_zappy *server);

int	init_server(t_zappy *server)
{
  srand(time(NULL));
  server->max_id = 0;
  server->map = NULL;
  server->writeGui = NULL;
  if (!(server->listConn = create_list(CONN)))
    return (1);
  if (!(server->listTeam = create_list(TEAM)))
    return (2);
  if (!(server->listIA = create_list(IA)))
    return (3);
  if (!(server->listGUI = create_list(GUI)))
    return (4);
  if (!(server->listEGG = create_list(EGG)))
    return (4);
  if (!(server->listWrite = create_list(ANSWER)))
    return (5);
  if (init_resource_strings(server))
    return (6);
  if (!(server->incantation_requirements = init_inventories(server)))
    return (7);
  init_ptr_func_ia(server);
  init_ptr_func_gui(server);
  return (0);
}

static int	init_resource_strings(t_zappy *server)
{
  server->resources[Food] = "nourriture";
  server->resources[Linemate] = "linemate";
  server->resources[Deraumere] = "deraumere";
  server->resources[Sibur] = "sibur";
  server->resources[Mendiane] = "mendiane";
  server->resources[Phiras] = "phiras";
  server->resources[Thystame] = "thystame";
  server->resources[7] = "joueur";
  server->resources[8] = NULL;
  server->nb_players[0] = 1;
  server->nb_players[1] = 2;
  server->nb_players[2] = 2;
  server->nb_players[3] = 4;
  server->nb_players[4] = 4;
  server->nb_players[5] = 6;
  server->nb_players[6] = 6;
  return (0);
}

static void	init_ptr_func_ia(t_zappy *server)
{
  server->ptr_func_ia[MOVE] = &move;
  server->ptr_func_ia[RIGHT] = &right;
  server->ptr_func_ia[LEFT] = &left;
  server->ptr_func_ia[SEE] = &see;
  server->ptr_func_ia[INVENTORY] = &inventory;
  server->ptr_func_ia[TAKE_OBJ] = &take_obj;
  server->ptr_func_ia[PUT_OBJ] = &put_obj;
  server->ptr_func_ia[EXPULSE] = &expulse;
  server->ptr_func_ia[BROADCAST] = &broadcast;
  server->ptr_func_ia[INCANTATION] = &incantation;
  server->ptr_func_ia[FORK] = &_fork;
  server->ptr_func_ia[CONNECT_NBR] = &connect_nbr;
}

static void	init_ptr_func_gui(t_zappy *server)
{
  server->ptr_func_gui[MSZ] = &msz;
  server->ptr_func_gui[BCT] = &bct;
  server->ptr_func_gui[MCT] = &mct;
  server->ptr_func_gui[TNA] = &tna;
  server->ptr_func_gui[PPO] = &ppo;
  server->ptr_func_gui[PLV] = &plv;
  server->ptr_func_gui[PIN] = &pin;
  server->ptr_func_gui[SGT] = &sgt;
  server->ptr_func_gui[SST] = &sst;
}

void	set_connect_nbr(t_zappy *server)
{
  t_node *teams;

  teams = server->listTeam->head;
  while (teams)
    {
      ((t_team *)(teams->data))->nb_slots_max = server->nbClients;
      teams = teams->next;
    }
}
