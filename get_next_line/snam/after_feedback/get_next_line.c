/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snam <snam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:42:38 by snam              #+#    #+#             */
/*   Updated: 2021/06/03 22:30:35 by snam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_next_line(int fd, char **line)
{
	static char		*fd_backup[OPEN_MAX];
	int				ret;

	if ((read(fd, "", 0) == -1) || !line || BUFFER_SIZE <= 0)
		return (-1);
	if ((ret = concat_old_backup(&fd_backup[fd], line)))
		return (ret);
	if ((ret = read_file(line, fd_backup, fd)))
		return (ret);
	return (0);
}

int			concat_old_backup(char **fd_backup, char **line)
{
	int				flag;

	if (*fd_backup != 0)
	{
		flag = split_str(line, fd_backup);
		if (flag == 1)
			return (1);
		else if (flag == -1)
			return (-1);
	}
	else
	{
		if (!(*line = (char *)malloc(1)))
			return (-1);
		**line = 0;
	}
	return (0);
}

int			read_file(char **line, char **fd_backup, int fd)
{
	char			*buf;
	long			read_size;
	int				ret;

	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = 0;
		ret = concat_new_buf(line, &fd_backup[fd], &buf);
		if (ret == 1)
			return (1);
		else if (ret == -1)
		{
			free(buf);
			return (-1);
		}
		buf = (char*)malloc(read_size + 1);
	}
	free(buf);
	return (0);
}

int			concat_new_buf(char **line, char **fd_backup, char **buf)
{
	int ret;

	ret = split_str(fd_backup, buf);
	if (ret == -1)
		return (-1);
	if (!(*line = generate_ret_line(line, fd_backup)))
		return (-1);
	*fd_backup = *buf;
	*buf = 0;
	if (ret == 0)
		return (0);
	return (1);
}

char		*generate_ret_line(char **line, char **fd_backup)
{
	char	*ret;

	if (!*line || !*fd_backup)
		return (0);
	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(*line) + ft_strlen(*fd_backup) + 1))))
		return (0);
	ft_strncpy(ret, *line, ft_strlen(*line) + 1);
	ft_strlcat(ret, *fd_backup, ft_strlen(*line) + ft_strlen(*fd_backup) + 1);
	free(*line);
	free(*fd_backup);
	*fd_backup = 0;
	return (ret);
}
