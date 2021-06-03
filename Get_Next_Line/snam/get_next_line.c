/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:42:38 by snam              #+#    #+#             */
/*   Updated: 2021/06/03 14:47:04 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			concat_old_backup(char **fd_backup, char **line, char *buf)
{
	int				flag;

	if (*fd_backup != 0)
	{
		flag = split_str(line, fd_backup);
		if (flag != 0)
		{
			free(buf);
			if (flag == 1)
				return (1);
			else if (flag == -1)
				return (-1);
		}
	}
	else
	{
		if (!(*line = (char *)malloc(1)))
		{
			free(buf);
			return (-1);
		}
		**line = 0;
	}
	return (0);
}

char		*generate_ret_line(char **s1, char **s2)
{
	char	*ret;

	if (!*s1 || !*s2)
		return (0);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(*s2) + 1));
	if (!ret)
		return (0);
	ft_strncpy(ret, *s1, ft_strlen(*s1) + 1);
	ft_strlcat(ret, *s2, ft_strlen(*s1) + ft_strlen(*s2) + 1);
	free(*s1);
	free(*s2);
	*s2 = 0;
	return (ret);
}

int			concat_new_buf(char **line, char **fd_backup, char **buf)
{
	int flag_nl;

	flag_nl = split_str(fd_backup, buf);
	if (flag_nl == -1)
		return (-1);
	if (!(*line = generate_ret_line(line, fd_backup)))
		return (-1);
	*fd_backup = *buf;
	*buf = 0;
	if (flag_nl == 0)
		return (0);
	return (1);
}

int			read_file(char **line, char **fd_backup, char **buf, int fd)
{
	long			read_size;
	int				ret;

	while ((read_size = read(fd, *buf, BUFFER_SIZE)) > 0)
	{
		(*buf)[read_size] = 0;
		ret = concat_new_buf(line, &fd_backup[fd], buf);
		if (ret == 1)
			return (1);
		else if (ret == -1)
		{
			free(*buf);
			return (-1);
		}
		*buf = (char*)malloc(read_size + 1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		*fd_backup[OPEN_MAX];
	char			*buf;
	int				ret;

	if ((read(fd, "", 0) == -1) || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if ((ret = concat_old_backup(&fd_backup[fd], line, buf)))
		return (ret);
	if ((ret = read_file(line, fd_backup, &buf, fd)))
		return (ret);
	free(buf);
	return (0);
}
