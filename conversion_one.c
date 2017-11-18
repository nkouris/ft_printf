/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:17:55 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/17 17:19:42 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_s_null(t_flags *flags)
{
	int pad;
	int empty;

	empty = 0;
	pad = print_padding(flags, &empty);
	flags->n += write(1, "(null)", 6);
	if (pad > 0)
	{
		while (pad--)
			flags->n += write(1, " ", 1);
	}
}

void	conv_s(const char **format, t_flags *flags, va_list *args)
{
	int		strlen;
	int 	pad;
	char 	*str;
//	wchar_t *wstr;

	pad = -1;
	if (flags->lenmod[0] == 'l' || **format == 'S')
	{
		str = va_arg(*args, char *);
		/*
		wstr = va_arg(*args, wchar_t *);
		str = uchar_switch(wstr);
		*/
	}
	else
		str = va_arg(*args, char *);
	if (!str)
		conv_s_null(flags);
	else
	{
		strlen = ft_strlen((const char *)str);
		if (flags->fieldwidth > 0 || flags->precision > 0)
			pad = print_padding(flags, &strlen);
		flags->n += write(1, str, strlen);
		if (pad > 0)
		{
			while (pad--)
				flags->n += write(1, " ", 1);
		}
	}
}

static void	conv_d_i_u_owrite(t_flags *flags, char *str, int numlen, long lnum)
{
	int pad;
	
	if ((lnum < 0) || (flags->sign && lnum != 0))
	{
		numlen++;
		flags->printsign = 1;
	}
	pad = print_padding_num(flags, numlen, lnum);
	((lnum < 0) || (flags->sign && lnum != 0)) ? numlen -= 1 : numlen;
	flags->n += write(1, str, numlen);
	if (pad > 0)
	{
		while (pad--)
			flags->n += write(1, " ", 1); 
	}
}

void	conv_d_i(const char **format, t_flags *flags, va_list *args)
{
	char	str[64];
	int		num;
	int		relen;
	long	lnum;

	ft_memset(str, 0, 64);
	if (flags->lenmod[0] == 'l' || **format == 'D')
		lnum = va_arg(*args, long);
	else
	{
		num = va_arg(*args, int);
		lnum = (long)num;
	}
	relen = count_num_signed(lnum, (long)10);
	base_conv_signed(lnum, str, (long)10, relen);
	conv_d_i_u_owrite(flags, str, relen, lnum);
}

void	conv_o_u(const char **format, t_flags *flags, va_list *args)
{
	char			str[64];
	unsigned int	num;
	int				numlen;
	unsigned long	lnum;

	ft_memset(str, 0, 64);
/* 
 * explicit typecast of va_arg does not work explicitly, so, wrap to let
 * compiler do the work 
 */
	if (flags->lenmod[0] == 'l' || **format == 'U' || **format == 'O')
	{
		lnum = va_arg(*args, unsigned long);
		if (lnum < 4294967295)
			lnum = (unsigned long)(int)lnum;
	}
	else
	{
		num = va_arg(*args, unsigned int);
		lnum = (unsigned long)num;
	}
	numlen = count_num(lnum, (unsigned long)10);
	if (**format == 'o' || **format == 'O')
	{
		flags->altform ? flags->precision = numlen + 1 : flags->precision;
		flags->altform ? flags->preper = 1 : flags->preper;
		numlen = base_conv(lnum, str, (long)8, numlen);
	}
	else
		numlen = base_conv(lnum, str, (long)10, numlen);
	conv_d_i_u_owrite(flags, str, numlen, 0);
}
