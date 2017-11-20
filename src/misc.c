/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:54:39 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/15 16:48:42 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*uchar_switch(wchar_t *wstr)
{
	wstr = 0;
	return (0);
}

void	upper(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			*str -= 32;
		str++;
	}
}
