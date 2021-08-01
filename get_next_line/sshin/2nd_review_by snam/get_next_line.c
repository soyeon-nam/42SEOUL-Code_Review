/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swshin <swshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:57:47 by sshin             #+#    #+#             */
/*   Updated: 2021/06/15 00:14:16 by swshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//코드들이 전반적으로 알아보기 쉬움 ^0^b

int	get_next_line(int fd, char **line)
{
	static char *backup[OPEN_MAX];
	int 		idx_to_split;
	int 		read_file_ret;

	if (BUFFER_SIZE < 1 || fd < 0 || OPEN_MAX <= fd || line == NULL || read(fd, "", 0) == _ERROR)
		return (_ERROR);
	if ((idx_to_split = get_idx_to_split(backup[fd])) == _LF_NOT_FOUND)
		read_file_ret = read_file(fd, &backup[fd], &idx_to_split);
	else
		return (split_line(&backup[fd], line, idx_to_split));
	if (read_file_ret == _ERROR)
		return (_ERROR);
	else if (read_file_ret == _LF_FOUND)
		return (split_line(&backup[fd], line, idx_to_split));
	else
		return (assign_last_line(&backup[fd], line));
}

int	get_idx_to_split(char *backup_fd)
{
	int idx;

	if (backup_fd == NULL)
		return (_LF_NOT_FOUND);
		//전에 리턴 값 변수로 하지말고 숫자로 하라고 본 거 같기도 한데, 정확하지는 않아서 좀 더 찾아보겠습니다.
	idx = 0;
	while (backup_fd[idx])
	{
		if (backup_fd[idx] == '\n')
			return (idx);
		++idx;
	}
	return (_LF_NOT_FOUND);
}

int	read_file(int fd, char **backup_fd, int *idx_to_split)
{
	char 	*buf;
	char 	*tmp;
	int		read_size;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		// return (_ERROR);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (!(tmp = ft_strjoin(*backup_fd, buf)))
		// {
		// 	free(buf);
		// 	return (_ERROR);
		// }
		free(*backup_fd);

		if (!(*backup_fd = ft_strdup(tmp))) // *backup_fd = tmp 으로 바꾸면 많은 부분에서 절약될 거 같습니다.
		// {
		// 	free(buf);
		// 	free(tmp);
		// 	return (_ERROR);
		// }

		free(tmp);
		if ((*idx_to_split = get_idx_to_split(*backup_fd)) != _LF_NOT_FOUND)
		{
			free(buf);
			return (_LF_FOUND);
		}
	}
	// EOF has been reached.
	free(buf);
	return (_GO_TO_ASSIGN_LAST_LINE);
}

int	split_line(char **backup_fd, char **line, int idx_to_split)
{
	char *tmp;

	(*backup_fd)[idx_to_split] = '\0';
	if (!(*line = ft_strdup(*backup_fd)))
	// {
	// 	free(*backup_fd);
	// 	return (_ERROR);
	// }
	tmp = ft_strdup(*backup_fd + idx_to_split + 1); //쪼개어 정리하기가 깔끔합니다.
	free(*backup_fd);
	*backup_fd = tmp;
	return (_A_LINE);
}

int	assign_last_line(char **backup_fd, char **line)
{
	if (*backup_fd)
	{
		*line = *backup_fd;
		*backup_fd = NULL;
		return (_EOF);
	}
	if (!(*line = ft_strdup(""))) //ft_strdup을 이곳저곳 잘 활용하셨네요.
	// {
	// 	free(*backup);
	// 	return (_ERROR);
	// }
	return (_EOF);
}
