/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:54:39 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/22 15:59:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	re_assigned(t_flags *flags, char *new)
{
	free(flags->str);
	flags->str = 0;
	flags->str = new;
}

int			buf_store(t_flags *flags, int n,
					const char *store, unsigned char pad)
{
	int		i;
	char	*new;

	i = 0;
	new = 0;
	if (store)
	{
		while (flags->strx < (512 * (flags->strinst + 1)) && --n >= 0)
			flags->str[flags->strx++] = store[i++];
	}
	else if (pad)
	{
		while (flags->strx < (512 * (flags->strinst + 1)) && --n >= 0
				&& i++ >= 0)
			flags->str[flags->strx++] = pad;
	}
	if (flags->strx == (512 * (flags->strinst + 1)))
	{
		flags->strinst++;
		if (new == ft_memalloc(512 + flags->strx))
			return(-1);
		re_assigned(flags, new);
	}
	return (i);
}

char		*uchar_switch(wchar_t *wstr)
{
	wstr = 0;
	return (0);
}

void		upper(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			*str -= 32;
		str++;
	}
}

void		conv_n(t_flags *flags, va_list *args)
{
	unsigned int *storage;

	storage = va_arg(*args, unsigned int *);
	*storage = flags->n;
}
