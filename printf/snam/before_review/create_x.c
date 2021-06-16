/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 09:55:05 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 11:46:58 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft		g_tag;

static void		set_print_numbers_x(int *size_width, int *size_precision, unsigned int num);
static void		print_x(char mode, unsigned int nb);

void			create_x(char mode, va_list ap)
{
	unsigned int		num;
	int					size_width;
	int					size_precision;

	num = va_arg(ap, unsigned int);
	set_print_numbers_x(&size_width, &size_precision, num);

	if (g_tag.flag_bar == 0)
	{
		if (g_tag.flag_zero > 0 && size_precision < 0)
			ft_put_affix(&size_width, '0');
		else
			ft_put_affix(&size_width, ' ');
	}
	if (g_tag.precision >= 0)
		ft_put_affix(&size_precision, '0');

	print_x(mode, num);
	if (g_tag.flag_bar > 0)
		ft_put_affix(&size_width, ' ');
}

static void		set_print_numbers_x(int *size_width, int *size_precision, unsigned int num)
{
	int		size_num;

	*size_width = g_tag.width;
	*size_precision = g_tag.precision;
	size_num = count_digit_hex(num);

	set_print_numbers_positive(size_width, size_precision, size_num);
	if ((0 <= g_tag.precision && g_tag.precision <= size_num) && num == 0 && g_tag.precision != 1)
		(*size_width)++;
}

static void		print_x(char mode, unsigned int nb)
{
	if (mode == 'x')
		print_base_lower(nb);
	else
		print_base_upper(nb);
}
