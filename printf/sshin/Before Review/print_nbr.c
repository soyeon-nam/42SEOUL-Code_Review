/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swshin <swshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:10:34 by sshin             #+#    #+#             */
/*   Updated: 2021/06/15 00:51:18 by swshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// print_nbr 함수 첫번째 if문의 '!(info->prec == 0 && nbr == 0)' 조건에 대한 설명:
// "정밀도 옵션값이 0인 동시에 가변인자의 값이 0인 경우" 아무것도 출력하지 않아야 한다.
// 이를 구현하기 위해, 해당 조건에서 'len_to_print_nbr'에 'info->nbrlen' 즉, '1'을 할당하지 않고,
// 'info->prec' 즉, '0'을 할당한다.
// 이후 print_nbr_by_type 함수의 마지막 if문에서 해당 조건에서의 출력을 예외처리한다.
int		print_nbr(size_t nbr, t_info *info)
{
	int		len_to_print_nbr;
	int		len_to_print_padding;
	int		ret;

	get_nbr_info(&nbr, info);
	if ((info->prec < info->nbrlen) && !(info->prec == 0 && nbr == 0))
		len_to_print_nbr = info->nbrlen;
	else
		len_to_print_nbr = info->prec;
	len_to_print_padding = info->width - len_to_print_nbr;
	if ((info->type == 'd' || info->type == 'i') && info->sign < 0)
		len_to_print_padding -= 1;
	else if (info->type == 'p')
		len_to_print_padding -= 2;
	ret = 0;
	if (info->sign < 0 && info->zero == _ON)
		ret += write(_STDOUT, "-", 1);
	if (info->minus == _ON)
	{
		ret += print_nbr_by_prec(nbr, *info, len_to_print_nbr);
		ret += print_padding(*info, len_to_print_padding);
	}
	else
	{
		ret += print_padding(*info, len_to_print_padding);
		ret += print_nbr_by_prec(nbr, *info, len_to_print_nbr);
	}
	return (ret);
}

void	get_nbr_info(size_t *nbr, t_info *info)
{
	info->sign = get_sign(nbr, info->type);
	info->base = get_base(info->type);
	info->nbrlen = get_nbrlen(*nbr, info->base);
}

int		print_nbr_by_prec(size_t nbr, t_info info, int len_to_print_nbr)
{
	int		ret;

	ret = 0;
	if (info.sign < 0 && info.zero == _OFF)
		ret += write(_STDOUT, "-", 1);
	ret += print_zero_by_prec(info, len_to_print_nbr);
	if (info.type == 'p')
		ret += write(_STDOUT, "0x", 2);
	ret += print_nbr_by_type(nbr, info);
	return (ret);
}

// print_zero_by_prec 함수의 역할에 대한 설명:
// 정밀도에 의해 추가적으로 '0' 패딩이 필요한 경우 즉, prec >= nbrlen인 경우 '0'을 추가로 패딩한다.
int		print_zero_by_prec(t_info info, int len_to_print_nbr)
{
	int		len_to_print_zero;
	int		ret;

	len_to_print_zero = len_to_print_nbr - info.nbrlen;
	ret = 0;
	while (len_to_print_zero > 0)
	{
		ret += write(_STDOUT, "0", 1);
		--len_to_print_zero;
	}
	return (ret);
}

int		print_nbr_by_type(size_t nbr, t_info info)
{
	char		*buf;
	char		*baseset;
	size_t		nbr_backup;
	int			ret;

	if (!(buf = (char *)malloc(sizeof(char) * (info.nbrlen + 1))))
		return (_ERROR);
	buf[info.nbrlen] = '\0';
	nbr_backup = nbr;
	baseset = get_baseset(info.type);
	while (info.nbrlen >= 1)
	{
		buf[info.nbrlen - 1] = baseset[nbr % info.base];
		nbr /= info.base;
		--(info.nbrlen);
	}
	ret = 0;
	if (!(nbr_backup == 0 && info.prec == 0))
	{
		ft_putstr_fd(buf, _STDOUT);
		ret += ft_strlen(buf);
	}
	free(buf);
	return (ret);
}
