/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:42:21 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/19 15:53:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_padding(t_flags *flags, int *strlen)
{
	int	pad;
	int	prec;

	pad = 0;
	prec = flags->precision;
	if (*strlen > prec && prec > 0)
		*strlen = prec;
	if (*strlen > flags->fieldwidth && flags->fieldwidth > 0)
		*strlen = flags->fieldwidth;
	else
		pad = flags->fieldwidth - *strlen;
	if (!flags->negwidth && pad > 0)
	{
		while (pad--)
			flags->n += write(1, " ", 1);
	}
	return (pad);
}

static void	print_prec_num(t_flags *flags, int p_pad, long lnum)
{
	if (lnum < 0)
		flags->n += write(1, "-", 1);
	else if (lnum >= 0 && flags->sign)
		flags->n += write(1, "+", 1);
	if ((!flags->negwidth && p_pad > 0) || flags->precision > 0)
	{
		while (p_pad-- > 0)
			flags->n += write(1, "0", 1);
	}
}

int			print_padding_num(t_flags *flags, int numlen, long lnum)
{
	int pad;
	int	prec;
	int p_pad;

	pad = 0;
	p_pad = 0;
	prec = flags->precision;
	numlen < flags->fieldwidth ? pad = flags->fieldwidth - numlen : pad;
	if (flags->printsign)
		numlen--;
	prec > 0 && prec > numlen ? p_pad = prec - numlen : p_pad;
	prec > 0 && prec > numlen ? pad = pad - p_pad : pad;
	if (flags->zpad && !p_pad)
	{
		p_pad = pad;
		!flags->negwidth ? pad = 0 : pad;
	}
	if ((!flags->negwidth) && pad > 0)
	{
		while (pad--)
			flags->n += write(1, " ", 1);
	}
	print_prec_num(flags, p_pad, lnum);
	return (pad);
}
