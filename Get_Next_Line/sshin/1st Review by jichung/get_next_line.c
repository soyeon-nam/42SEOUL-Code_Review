/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichung <jichung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:57:47 by sshin             #+#    #+#             */
/*   Updated: 2021/06/11 01:05:08 by jichung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 깃헙 리드미에 플로우차트가 있으니 참고하세요~!!

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	static char *backup[OPEN_MAX];
	int read_file_ret;
	int read_size;
	int idx_to_split;

	if (BUFFER_SIZE < 1 || fd < 0 || OPEN_MAX <= fd || !line)
		return (_ERROR);
	// Check if line feeds already exist in 'backup[fd]'.
	// Call the function 'read_file', only if there is no line feed in the 'backup[fd]'.
	if ((idx_to_split = get_idx_to_split(backup[fd])) == _LF_NOT_FOUND)
		read_file_ret = read_file(fd, &backup[fd], &read_size, &idx_to_split);
	else
		return (split_line(&backup[fd], line, idx_to_split));
	if (read_file_ret == _ERROR)
		return (_ERROR);
	else if (read_file_ret == _GO_TO_ASSIGN_LAST_LINE)
		return (assign_last_line(&backup[fd], line, read_size));
	else
		return (split_line(&backup[fd], line, idx_to_split));
}

int get_idx_to_split(char *backup)
{
	int idx;

	if (!backup)
		return (_LF_NOT_FOUND);
	idx = 0;
	while (backup[idx])
	{
		if (backup[idx] == '\n')
			return (idx);
		++idx;
	}
	return (_LF_NOT_FOUND);
}

int read_file(int fd, char **backup, int *read_size, int *idx_to_split)			//tmp free를 한번으로 가능한데 중복으로 쓰여서 줄이 길어짐. (임의 수정) -jichung
{																																						//0보다 크다는 것보다 _LF_NOT_FOUND가 아닐때가 더 명확하게 이해된다고 생각함. (임의 수정) -jichung
	char *buf;																																//buf free를 한번으로 가능한데 중복으로 쓰여서 줄이 길어짐. (임의 수정) -jichung
	char *tmp;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (_ERROR);
	while ((*read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[*read_size] = '\0';
		tmp = ft_strjoin(*backup, buf);
		free(buf);
		free(*backup);
		if (tmp == NULL)
			return (_ERROR);
		*backup = ft_strdup(tmp);
		free(tmp);
		if (*backup == NULL)
			return (_ERROR);
		if ((*idx_to_split = get_idx_to_split(*backup)) != _LF_NOT_FOUND)
			return (_LF_FOUND);
		if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (_ERROR);
	}
	// EOF has been reached.
	free(buf);
	return (_GO_TO_ASSIGN_LAST_LINE);
}

int split_line(char **backup, char **line, int idx_to_split)						//if와 else의 작성순서를 바꿨으면 free가 더욱 용이해졌으리라 생각됨. 그랬으면 노미넷을 지키기가 더 수월했을것. (임의 수정) -jichung
{
	char *tmp;

	(*backup)[idx_to_split] = '\0';
	*line = ft_strdup(*backup);
	if (*line == NULL)
	{
		free(*backup);
		return (_ERROR);
	}
	tmp = ft_strdup(*backup + idx_to_split + 1);
	free(*backup);
	*backup = tmp;
	return (_A_LINE);
}

int assign_last_line(char **backup, char **line, int read_size)
{
	if (read_size < 0)											//read 함수 결과값의 예외처리가 이 위치에 있는게 상당히 어색함 -jichung
		return (_ERROR);
	if (*backup == NULL)
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (_ERROR);
		return (_EOF);
	}
		*line = *backup;
		*backup = NULL;
		return (_EOF);
	}

//전반적으로 아주 잘 작성됨. 코드의 진행이 아주 심플한 점이 특히 인상깊었음. 그런데 노미넷 규정을 free를 중복으로 작성하여 어김으로서 일부 불필요하게 복잡해진 부분이 존재함. 그 이외에는 모두 완벽. -jichung