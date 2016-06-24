/*
** create_socket_tcp.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/network
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:58:23 2014
** Last update dim. juil. 13 21:39:50 2014 julien thebaud
*/

#include	<stdio.h>
#include	<netdb.h>
#include	<unistd.h>
#include	<stdbool.h>
#include	<sys/socket.h>
#include	"zappy.h"

static bool	perror_and_close(const char *str, int fdsock);

bool		create_socket_TCP(t_zappy *server)
{
  SOCKADDR_IN	serv_in;
  PROTOENT	*pe;
  int		sd;
  int		opt;

  opt = 1;
  pe = getprotobyname("TCP");
  if (!pe)
    sd = socket(AF_INET, SOCK_STREAM, 0);
  else
    sd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (sd == -1)
    return (perror_and_close("Socket failed. Error", -1));
  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    return (perror_and_close("Setsockopt failed. Error", sd));
  serv_in.sin_family = AF_INET;
  serv_in.sin_addr.s_addr = INADDR_ANY;
  serv_in.sin_port = htons(server->port);
  if (bind(sd, (SOCKADDR*)&serv_in, sizeof(serv_in)) == -1)
    return (perror_and_close("Bind failed. Error", sd));
  if (listen(sd, SOMAXCONN) == -1)
    return (perror_and_close("Listen failed. Error", sd));
  server->max_sd = sd;
  server->listen = sd;
  return (true);
}

static bool	perror_and_close(const char *str, int fdsock)
{
  if (str)
    perror(str);
  else
    perror("");
  if (fdsock != -1)
    {
      if (close(fdsock) == -1)
	perror("Close failed. Error");
    }
  return (false);
}
