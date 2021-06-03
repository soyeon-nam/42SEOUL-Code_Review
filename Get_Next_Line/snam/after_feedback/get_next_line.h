/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:43:05 by snam              #+#    #+#             */
/*   Updated: 2021/06/03 22:24:32 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE=1000
#endif

int				get_next_line(int fd, char **line);
int				concat_new_buf(char **line, char **fd_backup, char **buf);
int				concat_old_backup(char **fd_backup, char **line);
int				read_file(char **line, char **fd_backup, int fd);
char			*generate_ret_line(char **line, char **fd_backup);

int				split_str(char **dst, char **src);
int				sep_nl(char **dst, char **src, size_t size_src, size_t size_dst);
void			ft_strlcat(char *dst, const char *src, size_t size);
void			ft_strncpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);

#endif
