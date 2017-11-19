/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/19 14:34:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_x_write(t_flags *flags, char *str, int relen, int numlen)
{
	int		pad;

	relen = 0;
	if (flags->altform)
		numlen += 2;
	if (flags->zpad && flags->altform)
		flags->n += write(1, flags->pre, 2);
	pad = print_padding_num(flags, numlen, 0);
	if (!flags->zpad && flags->altform)
		flags->n += write(1, flags->pre, 2);
	flags->altform ? numlen -= 2 : numlen;
	flags->n += write(1, str, numlen);
	flags->altform ? numlen += 2 : numlen;
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, numlen, 0);
	}
}

void	conv_c(t_flags *flags, va_list *args)
{
	int				pad;
	unsigned int	nchar;
	wint_t 			wchar;
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
	flags->n += write(1, &nchar, 1);
   if (pad > 0)
   {
	   while (pad--)
		   flags->n += write(1, " ", 1);
   }
}

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
	(num = va_arg(*args, unsigned long)) >= HUINT && flags->lenmod[0] < 'j' ?
		num = 0 : num;
	numlen = count_num(num, 10);
	numlen = base_conv(num, str, 16, numlen);
	!num ? flags->altform = 0 : flags->altform;
	if (**format == 'X')
	{
		flags->pre = "0X";
		upper(str);
	}
	else
		(flags->pre) = "0x";
	flags->preper ? flags->zpad = 0 : flags->zpad;
	flags->negwidth ? flags->zpad = 0 : flags->zpad;
	flags->preper && num == 0 ? print_padding_num(flags, 0, 0) :
		conv_x_write(flags, str, relen, numlen);
}

void	conv_flag(t_flags *flags)
{
	int	pad;

	pad = 0;
	pad = print_padding_num(flags, 1, 0);
	flags->n += write(1, "%", 1);
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, 1, 0);
	}
}
