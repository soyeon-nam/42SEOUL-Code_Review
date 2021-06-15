/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 10:52:05 by sshin             #+#    #+#             */
/*   Updated: 2021/06/15 12:54:39 by sshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *fmt, ...)
{
	t_info		info;
	va_list		ap;
	int			ret;

	va_start(ap, fmt);
	ret = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			++fmt; // skip '%'
			parse_fmt(&fmt, ap, &info);
			ret += print_by_type(ap, &info);
			++fmt;
		}
		else
		{
			ret += write(_STDOUT, fmt, 1);
			++fmt;
		}
	}
	va_end(ap);
	return (ret);
}

void	parse_fmt(const char **fmt, va_list ap, t_info *info)
{
	init_opt_info(info);
	while (ft_strchr(_TYPE, **fmt) == NULL)
	{
		get_opt_info(**fmt, ap, info);
		++(*fmt);
	}
	if ((info->minus == _ON || info->prec > -1))
		info->zero = _OFF;
	info->type = **fmt;
}

void	get_opt_info(const char fmt, va_list ap, t_info *info)
{
	if (fmt == '0' && info->width == 0 && info->prec == -1)
		info->zero = _ON;
	else if (fmt == '-' && info->prec == -1)
		info->minus = _ON;
	else if (fmt == '.')
		info->prec = 0;
	else if (ft_isdigit(fmt))
		get_digit_info(fmt, info);
	else if (fmt == '*')
		get_aster_info(ap, info);
}

void	get_digit_info(const char fmt, t_info *info)
{
	if (info->prec == -1)
		info->width = info->width * 10 + (fmt - 48);
	else
		info->prec = info->prec * 10 + (fmt - 48);
}

void	get_aster_info(va_list ap, t_info *info)
{
	if (info->prec == -1)
	{
		info->width = va_arg(ap, int);
		if (info->width < 0)
		{
			info->minus = _ON;
			info->width *= -1;
		}
	}
	else
		info->prec = va_arg(ap, int);
}
