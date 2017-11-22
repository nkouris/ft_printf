/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_sc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:17:55 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/21 15:50:56 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_s_null(t_flags *flags)
{
	int pad;
	int empty;

	empty = 0;
	pad = print_padding(flags, &empty);
	flags->n += buf_store(flags, 6, "(null)", 0);
	if (pad > 0)
		flags->n += buf_store(flags, pad, 0, ' ');
}

void		conv_s(const char **format, t_flags *flags, va_list *args)
{
	int		strlen;
	int		pad;
	char	*str;

	pad = -1;
	if (flags->lenmod[0] == 'l' || **format == 'S')
		str = va_arg(*args, char *);
	else
		str = va_arg(*args, char *);
	if (!str)
		conv_s_null(flags);
	else
	{
		strlen = ft_strlen((const char *)str);
		if (flags->fieldwidth > 0 || flags->precision > 0)
			pad = print_padding(flags, &strlen);
		flags->n += buf_store(flags, strlen, str, 0);
		if (pad > 0)
			flags->n += buf_store(flags, pad, 0, ' ');
	}
}

void		conv_c(t_flags *flags, va_list *args)
{
	int				pad;
	unsigned int	nchar;
	wint_t			wchar;
	int				single;

	pad = 0;
	single = 1;
	if (flags->lenmod[0] == 'l')
	{
		wchar = va_arg(*args, wint_t);
		nchar = (unsigned int)wchar;
	}
	else
		nchar = va_arg(*args, unsigned int);
	pad = print_padding(flags, &single);
	if (!nchar)
	{
		flags->strx++;
		flags->n++;
	}
	flags->n += buf_store(flags, 1, 0, nchar);
	if (pad > 0)
		flags->n += buf_store(flags, pad, 0, ' ');
}

void		conv_flag(t_flags *flags)
{
	int pad;

	pad = 0;
	pad = print_padding_num(flags, 1, 0);
	flags->n += buf_store(flags, 1, 0, '%');
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, 1, 0);
	}
}

void		conv_n(t_flags *flags, va_list *args)
{
	unsigned int *storage;

	storage = va_arg(*args, unsigned int *);
	*storage = flags->n;
}
