/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/14 13:48:01 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	c_x_write(t_flags *flags, char *str, int clen, int numlen)
{
	int	pad;

	if (flags->altform)
		clen = clen + 2;
	if (flags->zpad && flags->altform)
		write(1, flags->pre, 2);
	pad = print_padding_num(flags, clen);
	if (!flags->zpad && flags->altform)
	{
		write(1, flags->pre, 2);
		clen = clen - 2;
	}
	write(1, &(str[numlen]), clen);
	if (pad > 0)
	{
		flags->neg_width = 1;
		print_padding_num(flags, clen);
	}
}

void	c_c(const char **format, t_flags *flags, va_list *args)
{
}

void	c_x(const char **format, t_flags, va_list *args)
{
	char	str[64];
	unsigned long	num;
	int				clen;
	int				numlen;

	clen = 0;
	ft_memset(str, 0, 64);
	num = va_arg(*args, unsigned long);
	numlen = count_num(num, (unsigned long)10);
	clen = base_conv(num, str, (unsinged long)16, numlen);
	if (numlen > clen)
		numlen = numlen - clen;
	if (!num)
		flags->alt_form = 0;
	if (**format == 'X')
	{
		ft_toupper(&(str[numlen]));
		flags->pre = "0X";
	}
	else
		(flags->pre) = "0x";
	c_x_write(flags, str, clen, numlen);
}
