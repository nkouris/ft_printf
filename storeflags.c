/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storeflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:25:09 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/14 15:27:18 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	store_pads(const char **format, t_flags *flags)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if (ft_isdigit && flags->fieldwidth < 0)
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
		flags->preperiod = 1;
		(*format)++;
		while (ft_isdigit(**format))
		{
			num = *(*format)++ - '0';
			i = (i * 10) + num;
			flags->precision = i;
		}
	}
}

void	store_pre(const char **format, t_flags *flags)
{
	int	i;

	i = 0;
	while (**format)
	{
		if (**format == 'l'
			|| **format == 'h'
			|| **format == 'j'
			|| **format == 'z')
			flags->pre[i++] = **format++;
		if (**format == '#' ? flags->altform = 1 : 0)
			(*format)++;
		if (**format == '0' ? flags->zpad = 1 : 0)
			(*format)++;
		if(**format == '-' ? flags->negwidth = 1 : 0)
			(*format)++;
		if (**format == ' ' ? flags->spacepad = 1 : 0)
			(*format)++;
		if (**format == '+' ? flags->pospad = 1 : 0)
			(*format)++;
		store_pads(format, flags);
		if (i == 2)
			break ;
	}
}
