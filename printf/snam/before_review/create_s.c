/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:03:14 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 11:46:33 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft		g_tag;
extern int		g_ret_print;

static void		set_print_numbers_s(int *size_width, int *size_precision, int size_num);
static void		print_s(char *str, int size_precision);

void			create_s(va_list ap)
{
	char	*str;
	int		size_width;
	int		size_precision;

	str = va_arg(ap, char *);
	set_print_numbers_s(&size_width, &size_precision, ft_strlen(str));
	if (!str)
	{
		if (size_precision >= 6 || size_precision < 0)
			size_width -= 6;
		else if (0 <= size_precision && size_precision < 6)
			size_width -= size_precision;
	}
	if (g_tag.flag_bar == 0)
		ft_put_affix(&size_width, ' ');
	print_s(str, size_precision);
	if (g_tag.flag_bar > 0)
		ft_put_affix(&size_width, ' ');
}

static void		set_print_numbers_s(int *size_width,
							int *size_precision, int size_num)
{
	*size_width = g_tag.width;
	*size_precision = g_tag.precision;
	if (g_tag.precision == 0)
		return ;
	else if (g_tag.precision <= size_num && g_tag.precision > 0)
		*size_width -= *size_precision;
	else
		*size_width -= size_num;
}

static void		print_s(char *str, int size_precision)
{
	if (str)
	{
		if (size_precision >= 0)
			while (size_precision-- && *str)
				ft_putchar(*str++);
		else
			while (*str)
				ft_putchar(*str++);
	}
	else
	{
		if (size_precision >= 6 || size_precision < 0)
		{
			g_ret_print += 6;
			write(1, "(null)", 6);
		}
		else if (0 <= size_precision && size_precision < 6)
		{
			g_ret_print += size_precision;
			write(1, "(null)", size_precision);
		}
	}
}
