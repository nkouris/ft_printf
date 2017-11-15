/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:42:21 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/14 17:29:00 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		print_padding(t_flags flags, int *strlen)
{
	int	pad;
	int	width;
	int	prec;

	pad = 0;
	width = flags->fieldwidth;
	prec = flags->precision;
	if (*strlen > precision && precision > 0)
		*strlen = precision;
	if (*strlen > width && width > 0)
		*strlen = width;
	else
		pad = width - *strlen;
	if (!flags->negwidth && pad > 0)
	{
		while (pad--)
			write(1, " ", 1);
	}
	return (pad);
}
