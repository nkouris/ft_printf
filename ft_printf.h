#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft.h"

#define BASE_FLAGS "0123456789abcdef"

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
	char			*buf;
}					t_flags;

/* Dispatcher */

int	ft_printf(const char *format, ...);

/* Store Flags */

void	store_pre(const char **format, t_flags *flags);

/* Print Flags */

int		print_padding(t_flags *flags, int *strlen);
int		print_padding_num(t_flags *flags, int relen);

/* Conversion Flags One */

void	conv_s(const char **format, t_flags *flags, va_list *args);
void	conv_d_i(const char **format, t_flags *flags, va_list *args);
void	conv_o_u(const char **format, t_flags *flags, va_list *args);

/* Conversion Flags Two */

void	conv_p(t_flags *flags, va_list *args);
void	conv_x(const char **format, t_flags *flags, va_list *args);

/* Ulitobase */

int		count_num_signed(long n, long base);
int		count_num(unsigned long n, unsigned long base);
int		base_conv_signed(long n, char *address, long base, int len);
int		base_conv(unsigned long n, char *address, unsigned long base, int len);

/* Misc */

char	*uchar_switch(wchar_t *wstr);

#endif
