/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/16 14:44:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_x_write(t_flags *flags, char *str, int relen, int numlen)
{
/* x_write rework */
	int		pad;

	relen = 0;
	if (flags->altform)
	{
		numlen += 2;
		flags->n += 2;
	}	
	if (flags->zpad && flags->altform)
		write(1, flags->pre, 2);
	pad = print_padding_num(flags, numlen);
	if (!flags->zpad && flags->altform)
		write(1, flags->pre, 2);
	flags->altform ? numlen -= 2 : numlen;
	write(1, str, numlen);
	flags->n += numlen;
	flags->altform ? numlen += 2 : numlen;
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, numlen);
	}
/* x_write original
	int		pad;

	if (flags->altform)
	{
		relen += 2;
		flags->n += 2;
	}	
	if (flags->zpad && flags->altform)
		write(1, flags->pre, 2);
	pad = print_padding_num(flags, relen);
	if (!flags->zpad && flags->altform)
	{
		write(1, flags->pre, 2);
		relen = relen - 2;
	}
	write(1, &(str[numlen]), relen);
	flags->n += relen;
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, relen);
	}
*/
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
	write(1, &nchar, 1);
	flags->n++;
   if (pad > 0)
   {
	   while (pad--)
		   write(1, " ", 1);
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
/* numlen relen relationship reworked */
	numlen = count_num(num, (unsigned long)10);
	numlen = base_conv(num, str, (unsigned long)16, numlen);
/* orig
	numlen = count_num(num, (unsigned long)10);
	relen = base_conv(num, str, (unsigned long)16, numlen);
	numlen > relen ? numlen -= relen : numlen;
	numlen == relen ? numlen = 0 : numlen;
*/
	!num ? flags->altform = 0 : flags->altform;
	if (**format == 'X')
	{
		flags->pre = "0X";
		upper(str);
	}
	else
		(flags->pre) = "0x";
	flags->preper && num == 0 ? print_padding_num(flags, 0) :
		conv_x_write(flags, str, relen, numlen);
}

void	conv_flag(t_flags *flags)
{
	int	pad;

	pad = 0;
	pad = print_padding_num(flags, 1);
	write(1, "%", 1);
	flags->n++;
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, 1);
	}
}
