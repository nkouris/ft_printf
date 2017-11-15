/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:17:55 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/15 15:13:27 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conv_s(const char **format, t_flags *flags, va_list *args)
{
	int		strlen;
	int 	pad;
	char 	*str;
//	wchar_t *wstr;

	pad = -1;

	if (flags->lenmod[0] == 'l' || **format == 'S')
	{
		;
		/*
		wstr = va_arg(*args, wchar_t *);
		str = uchar_switch(wstr);
		*/
	}
	else
		str = va_arg(*args, char *);
	strlen = ft_strlen((const char *)str);
	if (flags->fieldwidth > 0 || flags->precision > 0)
		pad = print_padding(flags, &strlen);
	write(1, str, strlen);
	if (pad > 0)
	{
		while (pad--)
		{
			write(1, " ", 1);
			flags->n++;
		}
	}
}

static void	conv_d_i_u_owrite(t_flags *flags, char *str, int numlen, long lnum)
{
	int pad;

	if (lnum < 0 && flags->zpad)
	{
		write(1, "-", 1);
		numlen += 1;
	}
	pad = print_padding_num(flags, numlen);
	if (lnum < 0)
	{
		write(1, "-", 1);
		flags->n++;
	}
	else if (flags->pospad)
	{
		write(1, "+", 1);
		flags->n++;
	}
	write(1, str, numlen);
	flags->n += numlen;
	if (pad > 0)
	{
		flags->negwidth = 1;
		print_padding_num(flags, numlen);
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
	int				relen;
	unsigned int	lnum;

	ft_memset(str, 0, 64);
	if (flags->lenmod[0] == 'l'
			|| **format == 'U'
			|| **format == 'O')
		lnum = va_arg(*args, unsigned long);
	else
	{
		num = va_arg(*args, unsigned int);
		lnum = (unsigned long)num;
	}
	relen = count_num(lnum, (unsigned long)10);
	if (**format == 'o' || **format == 'O')
		relen = base_conv(lnum, str, (long)8, relen);
	else
		relen = base_conv(lnum, str, (long)10, relen);
	conv_d_i_u_owrite(flags, str, relen, lnum);
}
