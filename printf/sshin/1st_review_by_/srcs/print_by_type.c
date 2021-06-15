/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_by_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swshin <swshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:08:48 by sshin             #+#    #+#             */
/*   Updated: 2021/06/15 23:02:33 by swshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_by_type(va_list ap, t_info *info)
{
	if (info->type == 'c')
		return (print_char(va_arg(ap, int), *info));
	else if (info->type == 's')
		return (print_str(va_arg(ap, char *), *info));
	else if (info->type == 'p')
		return (print_nbr(va_arg(ap, unsigned long), info));
	else if (info->type == 'd' || info->type == 'i')
		return (print_nbr(va_arg(ap, int), info));
	else if (info->type == 'u' || info->type == 'x' || info->type == 'X')
		return (print_nbr(va_arg(ap, unsigned int), info));
	else // info->type == '%'
		return (print_char('%', *info));
}

int		print_char(char c, t_info info)
{
	int		len_to_print_padding;
	int		ret;

	len_to_print_padding = info.width - 1;
	ret = 0;
	if (info.minus == _ON)
	{
		ret += write(_STDOUT, &c, 1);
		ret += print_padding(info, len_to_print_padding);
	}
	else
	{
		ret += print_padding(info, len_to_print_padding);
		ret += write(_STDOUT, &c, 1);
	}
	return (ret);
}

int		print_padding(t_info info, int len_to_print_padding)
{
	char	padding;
	int		ret;

	padding = (info.zero == _ON && info.type != 's') ? '0' : ' ';
	ret = 0;
	while (len_to_print_padding > 0)
	{
		ret += write(_STDOUT, &padding, 1);
		--len_to_print_padding;
	}
	return (ret);
}

int		print_str(char *str, t_info info)
{
	int		len_to_print_str;
	int		len_to_print_padding;
	int		ret;

	if (str == NULL)
		str = "(null)";
	if (info.prec == -1 || (size_t)info.prec > ft_strlen(str))
		len_to_print_str = ft_strlen(str);
	else
		len_to_print_str = info.prec;
	len_to_print_padding = info.width - len_to_print_str;
	ret = 0;
	if (info.minus == _ON)
	{
		ret += print_str_by_prec(str, len_to_print_str);
		ret += print_padding(info, len_to_print_padding);
	}
	else
	{
		ret += print_padding(info, len_to_print_padding);
		ret += print_str_by_prec(str, len_to_print_str);
	}
	return (ret);
}

int		print_str_by_prec(char *str, int len_to_print_str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < len_to_print_str)
	{
		ret += write(_STDOUT, &str[i], 1);
		++i;
	}
	return (ret);
}
