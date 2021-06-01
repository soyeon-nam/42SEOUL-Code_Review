/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:56:52 by jichung           #+#    #+#             */
/*   Updated: 2021/06/01 22:09:00 by sshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	*strallcat(const char *s1, const char *s2)
{
	char	*res;
	// 반환값을 다루는 변수의 이름을 result와 res로 혼용하고 있다. 통일하는것이 가독성에 도움이 될것 같다. -sshin
	char	*tmp;

	// 세가지 경우에 따라 완전히 다르게 작동하는 사실상 세가지 기능을 하는 함수.
	// s1이 NULL인 경우 strdup, s2가 NULL인 경우 동적할당 1칸, 둘다 NULL이 아닌 경우 strjoin으로 기능.
	// 각 함수의 기능은 최대한 독립적으로 제작하는것이 좋음에 위배. 노미네트 때문이겠지만,, -sshin
	if (!s2)
		return ((char *)malloc(1));
	if (!s1)
	{
		if (!(res = (char *)malloc(ft_strlen(s2) + 1)))
			return (NULL);
		tmp = res;
		while (*s2)
			*tmp++ = *s2++;
		*tmp = '\0';
		return (res);
	}
	if (!(res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);

	tmp = res;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (res);
}

size_t	is_nl(const char *buf)
{
	size_t flag;

	flag = 0;
	if (!buf)
		return (flag);
	while (*buf)
	{
		if (*buf == '\n')
		{
			flag = 1;
			break ;
		}
		++buf;
	}
	return (flag);
}

size_t	count_til_nl(const char *buf)
{
	size_t count;

	count = 0;
	while (buf[count] != '\n')
		++count;
	return (count);
}

// split 함수가 주솟값을 반환하고 그 이후에 nl_in_buf, nl_in_backup 함수 내에서 최종 반환값이 결정되는데
// 논리의 길이가 길어져서 아쉽다. split 함수의 반환값이 1(혹은 -1)이 되도록 제작하여 return()안에서 바로 split 함수를 호출하도록 했으면 어땠을까. -sshin
char	**split_by_nl(char *s)
{
	char	**strs;
	size_t	i;

	if (!(strs = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(strs[0] = (char *)malloc(count_til_nl(s) + 1)))
	{
		free(strs);
		return (NULL);
	}
	i = -1;
	while (s[++i] != '\n')
		strs[0][i] = s[i];
	strs[0][i] = '\0';
	if (!(strs[1] = (char *)malloc(ft_strlen(s) - count_til_nl(s))))
	{
		free(strs[0]);
		free(strs);
		return (NULL);
	}
	i = -1;
	s += count_til_nl(s);
	while (s[++i])
		strs[1][i] = s[i + 1];
	return (strs);
}
