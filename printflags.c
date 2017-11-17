/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:42:21 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/16 18:51:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_padding(t_flags *flags, int *strlen)
{
	int	pad;
	int	width;
	int	prec;

	pad = 0;
	width = flags->fieldwidth;
	prec = flags->precision;
	if (*strlen > prec && prec > 0)
		*strlen = prec;
	if (*strlen > width && width > 0)
		*strlen = width;
	else
		pad = width - *strlen;
	if (!flags->negwidth && pad > 0)
	{
		while (pad--)
			flags->n += write(1, " ", 1);
	}
	return (pad);
}

static void	print_prec_num(t_flags *flags, int p_pad)
{
	if (p_pad > 0)
	{
		while (p_pad--)
			flags->n += write(1, "0", 1);
	}
}

int		print_padding_num(t_flags *flags, int numlen)
{
	int pad;
	int width;
	int	prec;
	int p_pad;

	pad = 0;
	p_pad = 0;
	width = flags->fieldwidth;
	prec = flags->precision;
	numlen < width ? pad = width - numlen : pad;
	if (flags->printsign)
		numlen--;
	if (prec > 0 && prec > numlen)
	{
		p_pad = prec - numlen;
		pad = pad - p_pad;
	}
	if ((!flags->negwidth) && pad > 0)
	{
		while (pad--)
			flags->zpad ? (flags->n += write(1, "0", 1)) :
				(flags->n += write(1, " ", 1));
	}
	print_prec_num(flags, p_pad);
	return (pad);
}
