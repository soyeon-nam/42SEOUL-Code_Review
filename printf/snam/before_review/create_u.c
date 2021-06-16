/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 22:50:43 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 11:46:30 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft		g_tag;

static void		set_print_numbers_u(int *size_width, int *size_precision, size_t num);

void			create_u(va_list ap)
{
	unsigned int		num;
	int					size_width;
	int					size_precision;

	num = va_arg(ap, unsigned int);
	set_print_numbers_u(&size_width, &size_precision, num);
	if (g_tag.flag_bar == 0 && size_width > 0)
	{
		if (g_tag.flag_zero > 0 && g_tag.precision < 0)
			ft_put_affix(&size_width, '0');
		else
			ft_put_affix(&size_width, ' ');
	}
	if (num < 0)
		ft_putchar('-');
	if (g_tag.precision >= 0)
		ft_put_affix(&size_precision, '0');
	ft_putnbr(num);
	if (g_tag.flag_bar != 0)
		ft_put_affix(&size_width, ' ');
}

static void		set_print_numbers_u(int *size_width, int *size_precision, size_t num)
{
	*size_width = g_tag.width;
	*size_precision = g_tag.precision;

	if (num < 0)
		set_print_numbers_negative(size_width, size_precision, count_digit_u(num)); //유효한가??
	else
		set_print_numbers_positive(size_width, size_precision, count_digit_u(num));
}
