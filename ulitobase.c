/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulitobase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:31:41 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/17 18:26:56 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_num_signed(long n, long base)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

int		count_num(unsigned long n, unsigned long base)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

int		base_conv_signed(long n, char *address, long base, int len)
{
	int relen;
	int baselen;

	relen = 0;
	baselen = count_num_signed(n, base);
	if (len != baselen)
		len = baselen;
	if (n < 0)
		n = n * -1;
	if (n == 0)
	{
		address[0] = '0';
		relen++;
	}
	while (n)
	{
		address[--len] = BASE_FLAGS[n % base];
		n = n / base;
		relen++;
	}
	return (relen);
}

int		base_conv(unsigned long n, char *address, unsigned long base, int len)
{
	int relen;
	int baselen;

	relen = 0;
	baselen = count_num(n, base);
/* baselen and len rework */
	if (baselen != len)
		len = baselen;
	if (!n)
	{
		address[0] = '0';
		relen++;
	}
	while (n)
	{
		address[--len] = BASE_FLAGS[n % base];
		n = n / base;
		relen++;
	}
	return (relen);
}
