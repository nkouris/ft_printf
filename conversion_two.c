/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/14 22:30:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_x_write(t_flags *flags, char *str, int relen, int numlen)
{
	int		pad;

	if (flags->altform)
		relen = relen + 2;
	if (flags->zpad && flags->altform)
		write(1, flags->pre, 2);
	pad = print_padding_num(flags, relen);
	if (!flags->zpad && flags->altform)
	{
		write(1, flags->pre, 2);
		relen = relen - 2;
	}
	write(1, &(str[numlen]), relen);
	if (pad > 0)
	{
		while (pad--)
			write(1, " ", 1);
	}
}
/*
void	c_c(const char **format, t_flags *flags, va_list *args)
{
}
*/
void	conv_p(t_flags *flags, va_list *args)
{
	char *pass;
	char set;

	if (flags->lenmod[0] == 'l')
		set = 'X';
	else
		set = 'x';
	pass = &set;
	flags->altform = 1;
	conv_x((const char **)&pass, flags, args);
}

void	conv_x(const char **format, t_flags *flags, va_list *args)
{
	char			str[64];
	unsigned long	num;
	int				relen;
	int				numlen;

	relen = 0;
	ft_memset(str, 0, 64);
	num = va_arg(*args, unsigned long);
	numlen = count_num(num, (unsigned long)10);
	relen = base_conv(num, str, (unsigned long)16, numlen);
	if (numlen > relen)
		numlen = numlen - relen;
	if (!num)
		flags->altform = 0;
	if (**format == 'X')
		flags->pre = "0X";
	else
		(flags->pre) = "0x";
	conv_x_write(flags, str, relen, numlen);
}
