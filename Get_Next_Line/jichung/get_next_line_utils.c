/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichung <jichung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:56:52 by jichung           #+#    #+#             */
/*   Updated: 2021/05/26 18:34:13 by jichung          ###   ########.fr       */
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
	char	*tmp;

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
