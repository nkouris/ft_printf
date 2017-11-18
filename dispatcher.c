/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:04:31 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/17 14:32:06 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
static int	check_conversions1(const char **format, s_conversion **print,
			s_pflags *flags, va_list *args)
{
	int res;

	if (**format == 'g' || **format == 'G')
		res = c_g(print, pre, args);
	else if (**format == 'f' || **format == 'F')
		res = c_f(print, pre, args);
	else if (**format == 'a' || **format == 'A')
		res = c_a(print, pre, args);
	else if (**format == 'n')
		res = c_n(print, pre, args);
	else if (**format == 'e' || **format == 'E')
		res = c_e(print, pre, args);
	else
		res = -1;
	return (res);
}
*/
static void	parse_conv(const char **format, t_flags *flags, va_list *args)
{
	int	empty;

	empty = 0;
	if (**format == 's' || **format == 'S')
		conv_s(format, flags, args);
	else if (**format == 'p')
		conv_p(flags, args);
	else if (**format == 'd' || **format == 'D'
			|| **format == 'i')
		conv_d_i(format, flags, args);
	else if (**format == 'o' || **format == 'O'
			|| **format == 'u' || **format =='U')
		conv_o_u(format, flags, args);
	else if (**format == 'x' || **format == 'X')
		conv_x(format, flags, args);
	else if (**format == '%')
		conv_flag(flags);
	else if (**format == 'c' || **format == 'C')
		conv_c(flags, args);
}

static void	clear_flags(t_flags *flags)
{
	flags->altform = 0;
	flags->zpad = 0;
	flags->negwidth = 0;
	flags->spacepad = 0;
	flags->sign = 0;
	flags->fieldwidth = -1;
	flags->precision = -1;
	flags->lenmod[0] = 0;
	flags->pre = 0;
	flags->preper = 0;
	flags->printsign = 0;
}

static void	naive_write(const char **format, int *i)
{
	while (**format != '%' && **format)
	{
		(*format)++;
		(*i)++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list 		args;
	const char		*naive;
	t_flags			flags;
	int				i;

	flags.n = 0;
	va_start(args, format);
	while (*format)
	{
		clear_flags(&flags);
		naive = format;
		i = 0;
		naive_write(&format, &i);
	/* Store current amount of chars written and write */
		flags.n += write(1, naive, i);
	/* Store preproccess flags */
		store_pre(&format, &flags);
	/* Parse conversion and print */
		parse_conv(&format, &flags, &args);
	/* Move past conversion flag, unless at end of string */
		*format ? format++ : format;
	}
	va_end(args);
	return(flags.n);
}
