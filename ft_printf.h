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
	unsigned int	preperiod : 1;
	unsigned int	pospad : 1;
	int				fieldwidth;
	int				precision;
	int				n;
	char			lenmod[2];
	char			*pre;
}					t_flags;

/* Dispatcher */

int	ft_printf(const char *format, ...);

/* Store Flags */

void	store_pre(const char **format, t_flags *flags);

/* Print Flags */

int		print_padding(t_flags *flags, int *strlen);

/* Conversion Flags One */

void	conv_s(const char **format, t_flags *flags, va_list *args);

/* Conversion Flags Two */

/* Misc */

char	*uchar_switch(wchar_t *wstr);

#endif
