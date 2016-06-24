/*
** release_node.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/struct
** 
** Made by 
** Login   <thebau_j@epitech.net>
** 
** Started on  Sun Jul 13 15:56:18 2014 
** Last update Sun Jul 13 15:56:19 2014 
*/

#include	<stdlib.h>
#include	"utils.h"
#include	"zappy.h"

static	void	free_for_ia(t_clientIA *ia);
static	void	free_for_gui(t_clientGUI *gui);

int	release_node(t_node *node, t_type type)
{
  t_clientIA	*ia;
  t_clientGUI	*gui;
  t_gui_answer	*answer;

  if ((type == IA) && (ia = ((t_clientIA*)node->data)))
    free_for_ia(ia);
  else if ((type == GUI) && ((gui = ((t_clientGUI*)node->data))))
    free_for_gui(gui);
  else if (type == PLAYER)
    {
      free(node);
      return (1);
    }
  else if (type == ANSWER)
    {
      if ((answer = ((t_gui_answer*)node->data)))
	free(answer->msg);
    }
  free_va_arg(2, node->data, node);
  return (0);
}

static	void	free_for_ia(t_clientIA *ia)
{
  if (ia->buff_read)
    free_va_arg(2, ia->buff_read->buf, ia->buff_read);
  if (ia->buff_write)
    free_va_arg(2, ia->buff_write->buf, ia->buff_write);
  free_va_arg(2, ia->inventory, ia->big_write);
}

static	void	free_for_gui(t_clientGUI *gui)
{
 release_list(gui->listWrite);
 if (gui->buff_read)
  free_va_arg(2, gui->buff_read->buf, gui->buff_read);
 if (gui->buff_write)
  free_va_arg(2, gui->buff_write->buf, gui->buff_write);
}
