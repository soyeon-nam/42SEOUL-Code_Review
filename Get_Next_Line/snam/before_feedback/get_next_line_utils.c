/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:43:00 by snam              #+#    #+#             */
/*   Updated: 2021/06/03 20:26:49 by sshin            ###   ########.fr       */
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
					// line, fd_backup
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
	// 두번째 매개변수는 인덱스로, 세번째 인덱스는 포인터에 직접 연산을 하는 이유?
	// cpy 함수보다 dup, join 함수 사용 시 매개변수 개수 줄어들어 오류발생 줄고 가독성 좋은것 같음.
	// backup에 다시 할당할 내용을 temp에 dup하고, backup 해제하고, temp의 주소를 backup에 할당하고, temp를 해제하는 식으로. -sshin
	free(temp);
	return (1);
}
						// line, fd_backup
						// ft_backup, buf
int			split_str(char **dst, char **src)
// 함수 기능의 독립성이 아쉽다, -sshin
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
					// 매개변수 순서 dst, src와 size_dst, size_src 통일하는것이 가독성에 도움이 될듯.
					// sep_nl 함수이름 쪼금 아쉽당,, -sshin
			return (-1);
		return (1);
	}
	*dst = *src;
	*src = 0;
	return (0);
}
