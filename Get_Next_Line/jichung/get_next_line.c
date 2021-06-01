/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:08:19 by jichung           #+#    #+#             */
/*   Updated: 2021/06/01 19:16:27 by sshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 취향의 영역이긴 하지만, 함수명은 동사로 작성하는것이 좋다는것이 일반론임. -sshin
static int	nl_in_backup(char **line, char **backup)
{
	char	**strs;
	int		result;

	result = 1;
	strs = split_by_nl(*backup);

	if (!(*line = strallcat(NULL, strs[0])))
		result = -1;
	free(*backup);
	if (result == 1)
		if (!(*backup = strallcat(NULL, strs[1])))
			result = -1;
	free(strs[0]);
	free(strs[1]);
	free(strs);
	return (result);
}

static int	read_fd(int fd, char **buf)
{
	char	*tmp;
	char	*buf_tmp;
	int		rb;

	if (!(tmp = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((rb = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[rb] = '\0';
		if (!(buf_tmp = strallcat(*buf, tmp)))
			rb = -1;
		free(*buf);
		free(tmp);
		if (!(*buf = strallcat(NULL, buf_tmp)))
			rb = -1;
		free(buf_tmp);
		if ((rb != -1) && is_nl(*buf))
			return (1);
		if (!(tmp = (char *)malloc(BUFFER_SIZE + 1)))
			rb = -1;
	}
	free(tmp);
	return (rb);
}

static int	nl_in_buf(char **buf, char **line, char **backup)
{
	char	**strs;
	int		result;

	result = 1;
	strs = split_by_nl(*buf);
	free(*buf);
	if (!(*line = strallcat(NULL, strs[0])))
		result = -1;
	if (!(*backup = strallcat(NULL, strs[1])))
		result = -1;
	free(strs[0]);
	free(strs[1]);
	free(strs);
	return (result);
}

// 코드를 논리 흐름에 따라 위에서 아래로 읽도록 배치하는것이 좋을것 같다. (get_next_line 함수를 가장 위로 배치)
// 다른 함수를 볼 때 가장 많이 참고하는것은 get_next_line 함수이기 때문.
// libft 함수를 최대한 활용했으면 좀 더 이해하기 쉬운 코드가 되었을것 같음. - sshin
int			get_next_line(int fd, char **line)
{
	char		*buf;
	// *backup 원소의 갯수를 256으로 제한하는 것은 256이상의 fd에 대해 동작하지 않음. (fd의 최대갯수는 시스템에 따라 상이함)
	// 기본 라이브러리 limits.h를 include 하여 OPEN_MAX 매크로를 사용하는것을 추천함. -sshin
	static char	*backup[256];
	int			result;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 255 || !line)
		return (-1);
	if (is_nl(backup[fd]))
		return (nl_in_backup(line, &backup[fd]));

	if (!(buf = strallcat(NULL, backup[fd])))
		return (-1);
	if (!backup[fd])
		*buf = '\0';
	free(backup[fd]);
	result = read_fd(fd, &buf);
	if (result == 1)
		return (nl_in_buf(&buf, line, &backup[fd]));
	if (result == 0)
	{
		if (!(*line = strallcat(NULL, buf)))
			result = -1;
		backup[fd] = NULL;
	}
	free(buf);
	return (result);
}
