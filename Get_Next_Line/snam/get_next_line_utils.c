/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:43:00 by snam              #+#    #+#             */
/*   Updated: 2021/06/03 14:37:29 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	ret;

	ret = 0;
	while (s[ret])
		++ret;
	return (ret);
}

void		ft_strncpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	while ((i + 1 < size) && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	if (size != 0)
		dst[i] = 0;
}

void		ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dst_len;

	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return ;
	i = 0;
	while ((i < size - dst_len - 1) && src[i])
	{
		dst[dst_len + i] = src[i];
		++i;
	}
	dst[dst_len + i] = '\0';
}

int			sep_nl(char **dst, char **src, size_t size_src, size_t size_dst)
{
	char	*temp;

	if (!(*dst = (char*)malloc(size_dst + 1)))
		return (-1);
	ft_strncpy(*dst, *src, size_dst + 1);
	temp = *src;
	if (!(*src = (char*)malloc(size_src + 1)))
	{
		free(*dst);
		*dst = 0;
		return (-1);
	}
	ft_strncpy(*src, &temp[size_dst + 1], size_src + 1);
	free(temp);
	return (1);
}

int			split_str(char **dst, char **src)
{
	unsigned int	size_src;
	unsigned int	size_dst;
	char			*src_ptr;

	src_ptr = *src;
	while (*src_ptr && *src_ptr != '\n')
		++src_ptr;
	if (*src_ptr == '\n')
	{
		size_dst = src_ptr - *src;
		size_src = ft_strlen(*src) - size_dst - 1;
		if ((sep_nl(dst, src, size_src, size_dst) == -1))
			return (-1);
		return (1);
	}
	*dst = *src;
	*src = 0;
	return (0);
}
