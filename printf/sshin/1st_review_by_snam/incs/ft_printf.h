/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 10:52:08 by sshin             #+#    #+#             */
/*   Updated: 2021/06/15 18:40:17 by sshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define _TYPE		"cspdiuxX%"

# define _ERROR		0
# define _STDOUT	1

# define _ON		1
# define _OFF		0

typedef struct	s_info
{
	int		minus;
	int		zero;
	int		width;
	int		prec;
	char	type;
	int		sign;
	int		base;
	int		nbrlen;
}				t_info;

/*
** ========== ft_printf.c ==========
*/
int				ft_printf(const char *fmt, ...);
int				print_general_str(const char **fmt);
void			parse_fmt(const char **fmt, va_list ap, t_info *info);
void			get_opt_info(const char fmt, va_list ap, t_info *info);
void			get_digit_info(const char fmt, t_info *info);
void			get_aster_info(va_list ap, t_info *info);

/*
** ========== print_by_type.c ==========
*/
int				print_by_type(va_list ap, t_info *info);
int				print_char(char c, t_info info);
int				print_padding(t_info info, int len_to_print_padding);
int				print_str(char *str, t_info info);
int				print_str_by_prec(char *str, int len_to_print_va);

/*
** ========== print_nbr.c ==========
*/
void			get_nbr_info(size_t *nbr, t_info *info);
int				print_nbr(size_t nbr, t_info *info);
int				print_nbr_by_prec(size_t nbr, t_info info, int len_to_print_nbr);
int				print_zero_by_prec(t_info info, int len_to_print_nbr);
int				print_nbr_by_type(size_t nbr, t_info info);

/*
** ========== ft_printf_utils.c ==========
*/
void			init_opt_info(t_info *info);
int				get_sign(size_t *nbr, char type);
int				get_base(char type);
char			*get_baseset(char type);
int				get_nbrlen(size_t nbr, int base);

#endif