/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_tag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 10:50:04 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 10:50:05 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft			g_tag;

void		reset_tag(void)
{
	g_tag.flag_bar = 0;
	g_tag.flag_zero = 0;
	g_tag.width = 0;
	g_tag.precision = -1;
	g_tag.check_minus_width = 0;
}
