/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichung <jichung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 03:09:44 by jichung           #+#    #+#             */
/*   Updated: 2021/05/28 17:24:47 by jichung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*strallcat(const char *s1, const char *s2);
size_t	is_nl(const char *buf);
size_t	count_til_nl(const char *buf);
char	**split_by_nl(char *s);
int		get_next_line(int fd, char **line);
#endif
