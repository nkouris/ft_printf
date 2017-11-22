/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storeflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:25:09 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/21 15:41:20 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	store_pads(const char **format, t_flags *flags)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if (ft_isdigit(**format) && flags->fieldwidth < 0 && **format != '0')
	{
		while (ft_isdigit(**format))
		{
			num = *(*format)++ - '0';
			i = (i * 10) + num;
			flags->fieldwidth = i;
		}
	}
	else if (**format == '.')
	{
		flags->preper = 1;
		(*format)++;
		while (ft_isdigit(**format))
		{
			num = *(*format)++ - '0';
			i = (i * 10) + num;
			flags->precision = i;
		}
	}
}

static void	store_pre1(const char **format, t_flags *flags)
{
	if (**format == ' ' ? flags->spacepad = 1 : 0)
		(*format)++;
	if (**format == '+' ? flags->sign = 1 : 0)
		(*format)++;
}

void		store_pre(const char **format, t_flags *flags)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (**format && !(ft_isalpha(**format)) && j < 2)
	{
		if (**format == '%' && j < 1)
			(*format)++ ? j++ : j;
		else if (**format == '%')
			j++;
		if (**format == '#' ? flags->altform = 1 : 0)
			(*format)++;
		if (**format == '0' ? flags->zpad = 1 : 0)
			(*format)++;
		if (**format == '-' ? flags->negwidth = 1 : 0)
			(*format)++;
		store_pre1(format, flags);
		store_pads(format, flags);
		while (((**format == 'l' || **format == 'j'
				|| **format == 'z' || **format == 'h') && i < 2))
			flags->lenmod[i++] = *(*format)++;
	}
}
