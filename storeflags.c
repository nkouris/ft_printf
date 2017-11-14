/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storeflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:25:09 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/14 15:08:35 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	store_pads(const char **format, t_flags *flags)
{
	if (ft_isdigit)
	{
		
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
