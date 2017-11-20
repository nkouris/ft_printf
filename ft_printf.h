/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:57:08 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/19 15:46:09 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "libft.h"
# include <wchar.h>

# define BASE_FLAGS "0123456789abcdef"
# define HUINT 4294967296
# define MINLONG_SAFE 9223372036854775808U

typedef struct		s_flags
{
	unsigned int	altform : 1;
	unsigned int	zpad : 1;
	unsigned int	negwidth : 1;
	unsigned int	spacepad : 1;
	unsigned int	preper : 1;
	unsigned int	sign : 1;
	unsigned int	printsign : 1;
	int				fieldwidth;
	int				precision;
	int				n;
	char			lenmod[2];
	char			*pre;
}					t_flags;

/*
** Dispatcher
*/

int					ft_printf(const char *format, ...);

/*
** Store Flags
*/

void				store_pre(const char **format, t_flags *flags);

/*
** Print Flags
*/

int					print_padding(t_flags *flags, int *strlen);
int					print_padding_num(t_flags *flags, int relen, long lnum);

/*
** Conversion Flags diou
*/

void				conv_d_i(const char **format, t_flags *flags,
					va_list *args);
void				conv_u(const char **format, t_flags *flags, va_list *args);
void				conv_o(const char **format, t_flags *flags, va_list *args);

/*
** Conversion Flags sc
*/

void				conv_s(const char **format, t_flags *flags, va_list *args);
void				conv_c(t_flags *flags, va_list *args);
void				conv_flag(t_flags *flags);

/*
** Conversion Flags xp
*/

void				conv_c(t_flags *flags, va_list *args);
void				conv_p(t_flags *flags, va_list *args);
void				conv_x(const char **format, t_flags *flags, va_list *args);

/*
** Ulitobase
*/

int					count_num_signed(long n, long base);
int					count_num(unsigned long n, unsigned long base);
int					base_conv_signed(long n, char *address, long base, int len);
int					base_conv(unsigned long n, char *address,
					unsigned long base, int len);

/*
** Misc
*/

char				*uchar_switch(wchar_t *wstr);
void				upper(char *str);

#endif
