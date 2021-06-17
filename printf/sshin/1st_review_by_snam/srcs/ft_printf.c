/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 10:52:05 by sshin             #+#    #+#             */
/*   Updated: 2021/06/17 17:03:32 by sshin            ###   ########.fr       */
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
	char *type;

	init_opt_info(info);
	type = "cspdiuxX%";
	while (ft_strchr(type, **fmt) == NULL)
	{
		get_opt_info(**fmt, ap, info);
		++(*fmt);
	}
	if ((info->minus == true || info->prec > -1))
		info->zero = false;
	info->type = **fmt;
}

void	get_opt_info(const char fmt, va_list ap, t_info *info)
{
	if (fmt == '0' && info->width == 0 && info->prec == -1)
		info->zero = true;
	else if (fmt == '-' && info->prec == -1)
		info->minus = true;
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
			info->minus = true;
			info->width *= -1;
		}
	}
	else
		info->prec = va_arg(ap, int);
}
