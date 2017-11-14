/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:04:31 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/14 14:33:52 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	push_modifiers(const char **format, char **pre)
{
	char	mods[3];
	char	*new;
	int		i;

	i = 0;
	ft_bzero((s_conversion *)mods);
	while (i < 2)
	{
		if (**format == l || **format == h || **format == j || **format == z)
			mods[i++] = *(*format)++;
		else
			break ;
	}
	if (i > 0)
	{
		*new = ft_strjoin((const char *)(*pre), (const char *)mods);
		*pre = new;
	}
	if (!*pre)
		return (-1);
	return (1);
}

static int	check_conversions1(const char **format, s_conversion **print,
			s_pflags *flags, va_list *args)
{
	int res;

	if (**format == 'g' || **format == 'G')
		res = c_g(print, pre, args);
	else if (**format == 'f' || **format == 'F')
		res = c_f(print, pre, args);
	else if (**format == 'a' || **format == 'A')
		res = c_a(print, pre, args);
	else if (**format == 'n')
		res = c_n(print, pre, args);
	else if (**format == 'e' || **format == 'E')
		res = c_e(print, pre, args);
	else
		res = -1;
	return (res);
}

static int	check_conversions0(const char **format, s_conversion **print,
			s_pflags *flags, va_list *args)
{
	int res;

	if (**format == 's' || **format == 'S')
		res = c_s(print, , args);
	else if (**format == 'p')
		res = c_p(print, pre, args);
	else if (**format == 'd' || **format == 'D')
		res = c_d(print, pre, args);
	else if (**format == 'i')
		res = c_i(print, pre, args);
	else if (**format == 'o' || **format == 'O')
		res = c_o(print, pre, args);
	else if (**format == 'u' || **format == 'U')
		res = c_u(print, pre, args);
	else if (**format == 'x' || **format == 'X')
		res = c_x(print, pre, args);
	else if (**format == 'c' || **format == 'C')
		res = c_c(print, pre, args);
	else
		res = check_conversions1(format, print, pre, args);
	return (res);
}

static int	check_flags(const char **format, char **pre, s_pflags *flags)
{
	int		i;
	char	*dpre;

	i = 0;
	while (!ft_isalpha(*format[i]))
		i++;
	if (!((*pre) = (char *)ft_memalloc(sizeof(char) * i)))
		return (-1);
	i = 0;
	dpre = *pre;
	while (!ft_isalpha(**format))
		(*pre)[i++] = *(*format)++;
	if (push_modifiers(format, pre) < 0
		|| store_prepro0(pre, flags) < 0
		|| !(*print = (s_conversion *)ft_memalloc(sizeof(s_conversion))))
		return (-1);
	ft_strdel(&dpre);
	return (1);
}

static void	clear_flags(t_flags *flags)
{
	flags->altform = 0;
	flags->zpad = 0;
	flags->negwidth = 0;
	flags->spacepad = 0;
	flags->pospad = 0;
	flags->n = 0;
	flags->fieldwidth = -1;
	flags->precision = -1;
	flags->lenmod = "\0\0";
	flags->pre = 0;
}

static void	naive_write(const char **format, int *i)
{
	while ((**format != '%' && **format)
			|| (**format == '%' && (*(*format) + 1) == '%'))
	{
		(**format == '%' && (*(*format) + 1) == '%') ? (*format += 2) :
			(*format)++;
		(*i++);
	}
}

int		ft_printf(const char *format, ...)
{
	va_list 		args;
	const char		naive;
	t_flags			flags;
	int				i;

	va_start(args, format);
	while (*format)
	{
		clear_flags(&flags);
		naive = format;
		i = 0;
		naive_write(&format, &i);
		write(1, naive, i);
		format++;
		store_pre(&format, &flags);
		format++;
	}
	return(1);
}
