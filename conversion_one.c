/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:17:55 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/14 13:31:31 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	c_d_i_u_owrite(t_flags *flags, char *str, int numlen, long lnum)
{
	int pad;

	pad = 0;
	if (lnum < 0 && flags->zpad)
	{
		write(1, "-", 1);
		numlen += 1;
	}
	pad = print_padding_num(flags, numlen);
	if (lnum < 0)
		write(1, "-", 1);
	print_precision_num(flags, numlen);
	write(1, str, numlen);
	if (pad)
	{
		flags->neg_width = 1;
		print_padding_num(flags, numlen);
	}
}

void	c_d_i(const char **format, t_flags *flags, va_list *args)
{
	char	str[64];
	int		num;
	int		numlen;
	long	lnum;

	ft_memset(str, 0, 64);
	if (flags->lenmod[0] == 'l' || **format == 'D')
		lnum = va_arg(*args, long);
	else
	{
		num = va_arg(*args, int);
		lnum = (long)num;
	}
	numlen = count_num_signed(lnum, (long)10);
	base_conv_signed(lnum, str, (long)10, numlen);
	c_d_i_u_owrite(flags, str, numlen, lnum);
}

void	c_o_u(const char **format, t_flags, *flags, va_list *args)
{
	char		str[64];
	unsigned int	num;
	int				numlen;
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
	numlen = count_num(lnum, (unsigned long)10);
	if (**format == 'o' || **format == 'O')
		numlen = base_conv(lnum, str, (long)8, numlen);
	else

