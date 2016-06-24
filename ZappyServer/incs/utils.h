#ifndef _UTILS_H_
# define _UTILS_H_

#include	<stdbool.h>
#include	<stdarg.h>

bool	is_digit(char *);
char	*get_param(char *str);
void	*free_va_arg(int nbparam, ...);
int	parse_two_int(char *cmd, unsigned int *a1, unsigned int *a2);

#endif
