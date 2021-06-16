/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 10:50:42 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 10:50:43 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft			g_tag;
extern int			g_ret_print;

void			ft_putchar(char c)
{
	write(1, &c, 1);
	g_ret_print++;
}

void			ft_put_affix(int *num, char c)
{
	while ((*num)-- > 0)
	{
		g_ret_print++;
		write(1, &c, 1);
	}
}

static void		ft_putnbr_print(long long nb)
{
	char 	a;

	a = nb % 10 + 48;
	nb = nb / 10;
	if (nb > 0)
		ft_putnbr_print(nb);
	write(1, &a, 1);
	g_ret_print++;
}

void			ft_putnbr(long long nb)
{
	if (nb == 0 && g_tag.precision == 0)
	{
		if (g_tag.width <= 0)
			return ;
		write(1, " ", 1);
		g_ret_print++;
		return ;
	}
	ft_putnbr_print(nb);
}
