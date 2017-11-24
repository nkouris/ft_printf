/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:54:39 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/24 13:10:33 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	re_assigned(t_flags *flags, char *new)
{
	new = ft_strcpy(new, (const char *)flags->str);
	free(flags->str);
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
		while (flags->strx < (512 * (flags->strinst + 1)) && --n >= 0 && i++ >= 0)
			flags->str[flags->strx++] = *store++;
	}
	else if (pad)
	{
		while (flags->strx < (512 * (flags->strinst + 1)) && --n >= 0 && i++ >= 0)
			flags->str[flags->strx++] = pad;
	}
	if (flags->strx == (512 * (flags->strinst + 1)))
	{
		flags->strinst++;
		if (!(new = (char *)ft_memalloc(512 + flags->strx)))
			return (flags->failure = 1);
		re_assigned(flags, new);
	}
	if (n > 0)
		buf_store(flags, n, store, pad);
	return (i);
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

int			kill_switch(t_flags *flags)
{
	if (flags->failure)
	{
		flags->n = -1;
		return (1);
	}
	else
		return (0);
}
