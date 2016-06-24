/*
** action_network.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:58:02 2014
** Last update Sun Jul 13 20:05:01 2014 courtu_r
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"zappy.h"

void	send_buffer(t_clientIA *client, const char *buffer)
{
  ssize_t	nbwrites;

  if (buffer)
    nbwrites = write(client->socket, buffer, strlen(buffer));
  else
    return ;
  if (nbwrites != ((ssize_t)strlen(buffer)))
    fprintf(stderr, "send() failed.\n");
  printf("%s", get_color_term(SEND));
  print_time();
  printf("Sending message to %d: %s", client->id, buffer);
  printf("%s", get_color_term(DISABLE));
  fflush(stdout);
}
