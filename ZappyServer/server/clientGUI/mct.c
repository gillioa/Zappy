/*
** mct.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/clientGUI
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:53:34 2014
** Last update dim. juil. 13 16:36:20 2014 julien thebaud
*/

#include	"zappy.h"

int	mct(t_zappy *server, t_clientGUI *client, char *cmd)
{
  t_gui_answer		*answer;

  (void)cmd;
  answer = create_gui_ans(tograph_send_map(server), 0);
  put_in_list(client->listWrite, answer);
  return (0);
}
