/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:43:05 by snam              #+#    #+#             */
/*   Updated: 2021/06/03 14:30:28 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

int				get_next_line(int fd, char **line);
int				concat_new_buf(char **line, char **fd_backup, char **buf);
char			*generate_ret_line(char **s1, char **s2);
int				concat_old_backup(char **fd_backup, char **line, char *buf);
int				read_file(char **line, char **fd_backup, char **buf, int fd);

int				split_str(char **dst, char **src);
int				sep_nl(char **dst, char **src, \
size_t size_src, size_t size_dst);
void			ft_strlcat(char *dst, const char *src, size_t size);
void			ft_strncpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
#endif
