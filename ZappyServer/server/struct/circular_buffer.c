/*
** circular_buffer.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/struct
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:55:55 2014
** Last update Sun Jul 13 17:50:57 2014 courtu_r
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	"zappy.h"
#include	"circular_buffer.h"

t_buff	*alloc_buff()
{
  t_buff	*buff;

  if ((buff = malloc(sizeof(*buff))) == NULL)
    {
      fprintf(stderr, "Malloc has failed in init_buff()\n");
      return (NULL);
    }
  buff->buf = malloc(sizeof(*(buff->buf)) * (SIZE + 1));
  if (!(buff->buf))
    {
      fprintf(stderr, "Malloc has failed in init_buff()\n");
      return (NULL);
    }
  bzero((buff->buf), SIZE + 1);
  buff->begPtr = buff->buf;
  buff->endPtr = buff->buf;
  buff->readCnt = 0;
  buff->writeCnt = 0;
  return (buff);
}

int	write_in_buff(int fd, t_buff *buff, bool display, int id)
{
  Uint	nbreads;
  Uint	sizeLeft;

  sizeLeft = check_size(buff);
  if ((nbreads = read(fd, (buff->endPtr), sizeLeft)) <= 0)
    return (nbreads);
  buff->writeCnt += nbreads;
  buff->endPtr += nbreads;
  if (buff->endPtr >= buff->buf + SIZE)
    buff->endPtr = buff->buf;
  if (display && can_write_buffer(buff))
    {
      printf("%s", get_color_term(RECV));
      print_time();
      printf("Received message from %d: ", id);
      print_cmd_buffer(buff);
      printf("%s", get_color_term(DISABLE));
      fflush(stdout);
    }
  return (nbreads);
}

char	*try_get_cmd(t_buff *buff)
{
  char	*tmp;

  tmp = (buff->begPtr);
  while (*tmp != '\n' && tmp != buff->endPtr)
    {
      tmp += 1;
      if (tmp >= buff->buf + SIZE)
	tmp = buff->buf;
    }
  if (*tmp != '\n')
    return (NULL);
  else
    return (get_cmd_from_buff(buff));
}

char	*finish_treating(t_buff **buff, char *str, int cnt)
{
  if (str)
    {
      str[cnt++] = '\n';
      str[cnt] = 0;
    }
  (*(*buff)->begPtr) = 0;
  (*buff)->begPtr += 1;
  if ((*buff)->begPtr >= (*buff)->buf + SIZE)
    (*buff)->begPtr = (*buff)->buf;
  (*buff)->readCnt += 1;
  return (str);
}

char	*get_cmd_from_buff(t_buff *buff)
{
  char	*str;
  Uint	cnt;
  char	*keepBeg;

  cnt = 0;
  keepBeg = buff->begPtr;
  str = NULL;
  while (*((buff)->begPtr) != '\n' && (buff->readCnt) < buff->writeCnt)
    {
      if ((str = realloc(str, sizeof(*str) * (3 + cnt))) == NULL)
	{
	  fprintf(stderr, "Malloc has failed\n");
	  return (NULL);
	}
      str[cnt] = (*buff->begPtr);
      cnt += 1;
      buff->readCnt += 1;
      (buff->begPtr) += 1;
      if (buff->begPtr >= buff->buf + SIZE)
        buff->begPtr = buff->buf;
    }
  if (!check_str(buff, str, keepBeg, cnt))
    return (NULL);
  return (finish_treating(&buff, str, cnt));
}
