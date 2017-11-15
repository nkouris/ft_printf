/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:42:21 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/15 14:21:26 by nkouris          ###   ########.fr       */
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
		{
			write(1, " ", 1);
			flags->n++;
		}
	}
	return (pad);
}

int		print_padding_num(t_flags *flags, int relen)
{
	int pad;
	int width;
	int	prec;

	pad = 0;
	width = flags->fieldwidth;
	prec = flags->precision;
	if (relen < width)
		pad = width - relen;
	if (prec > width)
	{
		flags->zpad = 1;
		pad = prec - relen;
	}
	if ((!flags->negwidth || prec > 0) && pad > 0)
	{
		while (pad--)
		{
			flags->zpad ? write(1, "0", 1) : write(1, " ", 1);
			flags->n++;
		}
	}
	return (pad);
}
