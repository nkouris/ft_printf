/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_diou.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:17:55 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/19 16:28:26 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_d_i_u_owrite(t_flags *flags, char *str, int numlen, long lnum)
{
	int	pad;

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

void		conv_d_i(const char **format, t_flags *flags, va_list *args)
{
	char	str[64];
	int		num;
	int		relen;
	long	lnum;

	ft_memset(str, 0, 64);
	if (flags->lenmod[0] >= 106 || **format == 'D')
		lnum = va_arg(*args, long);
	else
	{
		num = va_arg(*args, int);
		lnum = (long)num;
	}
	if (flags->lenmod[0] == 'h' && flags->lenmod[1] == 'h')
		lnum = (long)(char)num;
	else if (flags->lenmod[0] == 'h' && flags->lenmod[1] != 'h')
		lnum = (long)(short)num;
	relen = count_num_signed(lnum, 10);
	base_conv_signed(lnum, str, 10, relen);
	if (flags->spacepad && flags->fieldwidth < relen)
		flags->fieldwidth = relen + 1;
	if (flags->preper && !lnum)
		relen--;
	conv_d_i_u_owrite(flags, str, relen, lnum);
}

/*
** Explicit typecast in va_arg does not work explicitly, so, wrap to let
** compiler do the work
*/

void		conv_u(const char **format, t_flags *flags, va_list *args)
{
	char			str[64];
	int				numlen;
	unsigned long	lnum;

	ft_memset(str, 0, 64);
	if (flags->lenmod[0] >= 106 || **format == 'U' || **format == 'O')
	{
		lnum = va_arg(*args, unsigned long);
		if (lnum < 4294967295)
			lnum = (unsigned long)(int)lnum;
	}
	else
		lnum = (unsigned long)va_arg(*args, unsigned int);
	numlen = base_conv(lnum, str, 10, 1);
	flags->sign = 0;
	if (flags->preper && !lnum)
		numlen--;
	conv_d_i_u_owrite(flags, str, numlen, 0);
}

void		conv_o(const char **format, t_flags *flags, va_list *args)
{
	char			str[64];
	int				numlen;
	unsigned long	lnum;

	ft_memset(str, 0, 64);
	if (flags->lenmod[0] >= 106 || **format == 'O')
	{
		lnum = va_arg(*args, unsigned long);
		if (lnum < 4294967295)
			lnum = (unsigned long)(int)lnum;
	}
	else
		lnum = (unsigned long)va_arg(*args, unsigned int);
	numlen = count_num(lnum, (unsigned long)10);
	if (flags->altform)
	{
		lnum ? flags->precision = numlen + 1 :
			(flags->precision = 1);
		flags->preper = 1;
	}
	numlen = base_conv(lnum, str, (long)8, numlen);
	if (flags->preper && !lnum)
		numlen--;
	conv_d_i_u_owrite(flags, str, numlen, 0);
}