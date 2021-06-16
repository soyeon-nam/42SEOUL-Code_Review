/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cppc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:50:04 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 11:47:07 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft		g_tag;
extern int		g_ret_print;

void			create_c(va_list ap)
{
	char			c;
	int				size;

	c = va_arg(ap, int);
	size = g_tag.width - 1;
	if (g_tag.flag_bar == 0 && size > 0)
		ft_put_affix(&size, ' ');
	ft_putchar(c);
	if (g_tag.flag_bar != 0 && size > 0)
		ft_put_affix(&size, ' ');
}

void			create_percent(void)
{
	int		size;

	size = g_tag.width - 1;
	if (g_tag.flag_bar == 0 && size > 0)
	{
		if (g_tag.flag_zero > 0)
			ft_put_affix(&size, '0');
		else
			ft_put_affix(&size, ' ');
	}
	ft_putchar('%');
	if (g_tag.flag_bar != 0 && size > 0)
		ft_put_affix(&size, ' ');
}

void			create_p(va_list ap)
{
	size_t			pointer;
	int				size;
	int				size_width;

	pointer = (size_t)va_arg(ap, char *);
	if (pointer == 0 && g_tag.precision == 0)
		size = 0;
	else
		size = count_digit_hex(pointer);
	size_width =g_tag.width - size - 2;
	if (g_tag.flag_bar == 0 && size_width > 0)
		ft_put_affix(&size_width, ' ');
	write(1, "0x", 2);
	g_ret_print += 2;
	print_base_lower(pointer);
	if (g_tag.flag_bar != 0 && size_width > 0)
		ft_put_affix(&size_width, ' ');
}
