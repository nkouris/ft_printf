#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft.h"

typedef struct		s_flags
{
	unsigned int	altform : 1;
	unsigned int	zpad : 1;
	unsigned int	negwidth : 1;
	unsigned int	spacepad : 1;
	unsigned int	pospad : 1;
	int				fieldwidth;
	int				precision;
	int				n;
	char			lenmod[2];
	char			*pre;
}					t_flags;

/* Dispatcher */

ft_printf(

/* Store Flags */

/* Process Flags */

/* Conversion Flags One */

/* Conversion Flags Two */
