/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:03:04 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 11:46:50 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft		g_tag;

static void		set_print_numbers_di(int *size_width, int *size_precision, int num);
static void		create_di_prefix(int size_precision, int *size_width, int minus_flag);

void			create_di(va_list ap)
{
	long long		num;
	int				size_width;
	int				size_precision;
	int				minus_flag;

	num = va_arg(ap, int);
	minus_flag = (num < 0 ? 1 : 0);
	set_print_numbers_di(&size_width, &size_precision, num);
	num = (num < 0 ? -num : num);

	create_di_prefix(size_precision, &size_width, minus_flag);
	if (g_tag.precision >= 0)
		ft_put_affix(&size_precision, '0');
	ft_putnbr(num);
	if (g_tag.flag_bar > 0)
		ft_put_affix(&size_width, ' ');
}

static void		set_print_numbers_di(int *size_width, int *size_precision, int num)
{
	*size_width = g_tag.width;
	*size_precision = g_tag.precision;

	if (num < 0)
		set_print_numbers_negative(size_width, size_precision, count_digit(num));
	else
		set_print_numbers_positive(size_width, size_precision, count_digit(num));
}

static void		create_di_prefix(int size_precision,
							int *size_width, int minus_flag)
{
	if (g_tag.flag_bar == 0)
	{
		if (g_tag.flag_zero > 0 && size_precision < 0)
		{
			if (minus_flag)
				ft_putchar('-');
			ft_put_affix(size_width, '0');
		}
		else
		{
			ft_put_affix(size_width, ' ');
			if (minus_flag)
				ft_putchar('-');
		}
	}
	if (g_tag.flag_bar != 0 && minus_flag)
		ft_putchar('-');
}
