/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_print_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:40:40 by marvin            #+#    #+#             */
/*   Updated: 2021/06/15 18:40:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft			g_tag;

void		set_print_numbers_negative(int *size_width, int *size_precision, int size_num)
{
	if (g_tag.precision > size_num)
	{
		*size_width -= (g_tag.precision + 1);
		*size_precision -= size_num;
	}
	else if (g_tag.precision < 0)
	{
		*size_width -= (size_num + 1);
		*size_precision = -1;
	}
	else
	{
		*size_width -= (size_num + 1);
		*size_precision = 0;
	}
}

void		set_print_numbers_positive(int *size_width, int *size_precision, int size_num)
{
	if (g_tag.precision > size_num)
	{
		*size_width -= g_tag.precision;
		*size_precision -= size_num;
	}
	else if (g_tag.precision < 0)
	{
		*size_width -= size_num;
		*size_precision = -1;
	}
	else
	{
		*size_width -= size_num;
		*size_precision = 0;
	}
}

// void	set_width_prec(int *size_width, int *size_precision, int sub_width, int sub_pre)
// {
// 		*size_width -= sub_width;
// 		*size_precision -= sub_pre;
// }
