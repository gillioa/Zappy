#ifndef _TYPES_H
# define _TYPES_H

#include	<sys/select.h>
#include	<arpa/inet.h>

typedef int			SOCKET;
typedef struct sockaddr_in	SOCKADDR_IN;
typedef struct sockaddr		SOCKADDR;
typedef struct protoent		PROTOENT;
typedef struct timeval		TIMEVAL;

#define NB_COLOR_TERM	6

typedef enum e_color_term
{
  SERVER = 0,
  PLAYER_IA = 1,
  RECV = 2,
  SEND = 3,
  DISABLE = 4
} t_color;

#endif
