/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 10:50:49 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 10:51:14 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern t_ft		g_tag;
extern int			g_ret_print;

void		update_width(char c)
{
	g_tag.width *= 10;
	g_tag.width += (c - '0');
}

void		update_precision(char c)
{
	g_tag.precision *= 10;
	g_tag.precision += (c - '0');
}
