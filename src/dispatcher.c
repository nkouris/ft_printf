/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:04:31 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/22 15:02:43 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	else if (**format == 'o' || **format == 'O')
		conv_o(format, flags, args);
	else if (**format == 'u' || **format == 'U')
		conv_u(format, flags, args);
	else if (**format == 'x' || **format == 'X')
		conv_x(format, flags, args);
	else if (**format == '%')
		conv_flag(flags);
	else if (**format == 'c' || **format == 'C')
		conv_c(flags, args);
	else if (**format == 'n')
		conv_n(flags, args);
	else
		(*format)--;
}

static void	clear_flags(t_flags *flags)
{
	flags->altform = 0;
	flags->zpad = 0;
	flags->negwidth = 0;
	flags->spacepad = 0;
	flags->preper = 0;
	flags->sign = 0;
	flags->printsign = 0;
	flags->ptox = 0;
	flags->fieldwidth = -1;
	flags->precision = -1;
	flags->lenmod[0] = 0;
	flags->pre = 0;
	flags->strx = 0;
	flags->strinst = 0;
}

static void	naive_write(const char **format, int *i)
{
	while (**format != '%' && **format)
	{
		(*format)++;
		(*i)++;
	}
}

/*
** Store current amount of chars written and write
** Store preproccess flags
** Parse conversion and print
** Move past conversion flag, unless at end of string
*/

int			ft_printf(const char *format, ...)
{
	va_list			args;
	const char		*naive;
	t_flags			flags;
	int				i;

	flags.n = 0;
	va_start(args, format);
	while (*format)
	{
		if (!(flags.str = ft_memalloc(512)))
			exit(-1);
		clear_flags(&flags);
		naive = format;
		i = 0;
		naive_write(&format, &i);
		if (i)
			flags.n += buf_store(&flags, i, naive, 0);
		store_pre(&format, &flags);
		parse_conv(&format, &flags, &args);
		*format ? format++ : format;
		write(1, flags.str, (flags.strx * (flags.strinst + 1)));
		ft_memdel((void **)(&(flags.str)));
	}
	va_end(args);
	return (flags.n);
}
