#ifndef _CIRCULAR_BUFFER_H_
# define _CIRCULAR_BUFFER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#define SIZE 512

typedef unsigned int Uint;

typedef struct s_circBuff
{
  Uint	isReady;
  char	*buf;
  char	*begPtr;
  char	*endPtr;
  Uint	readCnt;
  Uint	writeCnt;
}t_buff;

void	print_cmd_buffer(t_buff *);
Uint	get_size_left(const char *, const char *);
Uint	is_filled(t_buff *);
Uint	check_size(t_buff *);
char	*check_str(t_buff *, char *, char *, int);
t_buff	*alloc_buff();
int	write_in_buff(int, t_buff *, bool, int);
char	*get_cmd_from_buff(t_buff *);
char	*try_get_cmd(t_buff *);
int	copy_in_buff(char *str, t_buff *buff);

#endif
