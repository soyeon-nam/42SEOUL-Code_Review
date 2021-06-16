/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 08:37:37 by snam              #+#    #+#             */
/*   Updated: 2021/06/16 11:22:50 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			count_digit(int num)
{
	int		ret;

	ret = 1;
	if (ret < 0)
	{
		++ret;
		ret *= -1;
	}
	while (num /= 10)
		++ret;
	return (ret);
}

int			count_digit_u(unsigned int num)
{
	int		ret;

	ret = 1;
	while (num /= 10)
		++ret;
	return (ret);
}

int			count_digit_hex(size_t num)
{
	int		ret;

	ret = 1;
	while (num /= 16)
		++ret;
	return (ret);
}

size_t			ft_strlen(const char *s)
{
	size_t	ret;

	if (!s)
		return (0);
	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}
