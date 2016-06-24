/*
** utils_buffer.c for  in /home/thebau-j/rendu/blowshitup/ServerZappy/server/struct
**
** Made by
** Login   <thebau_j@epitech.net>
**
** Started on  Sun Jul 13 15:56:25 2014
** Last update dim. juil. 13 18:18:27 2014 julien thebaud
*/

#include	<stdlib.h>
#include	<string.h>
#include	"circular_buffer.h"

Uint	get_size_left(const char *endPtr, const char *buf)
{
  int	len;

  len = SIZE - (endPtr - buf);
  if (len >= 2)
    return (len);
  else if (len == 1)
    return (1);
  else
    return (0);
}

Uint	is_filled(t_buff *buff)
{
  if (buff->writeCnt > buff->readCnt)
    return (1);
  else
    return (0);
}

Uint	check_size(t_buff *buff)
{
  Uint	ret;

  if ((ret = get_size_left(buff->endPtr, buff->buf)))
    return (ret);
  printf("endPTR DECALAGE\n");
  buff->endPtr = buff->buf;
  return (get_size_left(buff->endPtr, buff->buf));
}

char	*check_str(t_buff *buff, char *str, char *keepBeg, int cnt)
{
  if (*(buff->begPtr) != '\n')
    {
      buff->begPtr = keepBeg;
      buff->readCnt -= cnt;
      free(str);
      return (NULL);
    }
  return ("");
}

int	copy_in_buff(char *str, t_buff *buff)
{
  Uint	cnt = 0;

  while (cnt < strlen(str))
    {
      *(buff->endPtr) = str[cnt];
      buff->writeCnt += 1;
      buff->endPtr += 1;
      if (buff->endPtr >= buff->buf + SIZE)
	buff->endPtr = buff->buf;
      cnt += 1;
    }
  return (strlen(str));
}
