/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:08:19 by jichung           #+#    #+#             */
/*   Updated: 2021/06/01 22:00:12 by sshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 취향의 영역이긴 하지만, 함수명은 동사로 작성하는것이 좋다는것이 일반론임. -sshin
static int	nl_in_backup(char **line, char **backup)
{
	char	**strs;
	int		result;
	// 변수를 사용 순서에 따라 아래와 같이 배치하는것이 좋을것 같다.
	// char	**strs;
	// int	result;  -sshin

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
	// read bytes 보다는 read size가 일반적인 표현인것 같다. -sshin
	while ((rb = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[rb] = '\0';
		// buf_tmp라는 변수명은 직관적이지 못하다.
		// 차라리 tmp1, tmp2 혹은 big_tmp, small_tmp로 구분하는것이 좀더 직관적이지 않을까? -sshin
		if (!(buf_tmp = strallcat(*buf, tmp)))
			// 여기서 rb변수를 read byte라는 변수명과 전혀 다른 의미로 사용하고 있다.
			// flag용 변수를 하나 더 선언하여 사용하는것이 좋지 않을까? 노미네트 때문이겠지만,, -sshin
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

// nl in backup, nl_in_buf 함수는 코드 12줄이 완전히 동일하다.
// 초기설계를 치밀하게 하였으면 두 함수를 합쳐서 좀더 심플한 구조로 만들 수 있었을것 같다. -sshin
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

// 표준함수를 최대한 활용했으면 좀 더 이해하기 쉬운 코드가 되었을것 같음. - sshin
// nl_in_backup, nl_in_buf 함수는 함수 내에서 (표준 라이브러리 함수가 아닌) '제작한 함수를 2개 호출'한다.
// 각 함수의 기능은 최대한 독립적으로 만드는것이 좋다는것에 위배됨. -sshin
int			get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*backup[256];
	int			result;
	// 변수의 선언은 사용 순서에 따라
	// static char *backup[256]
	// char *buf;
	// int result; 순으로 배치하는것이 좋을것 같음. -sshin

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 255 || !line)
		return (-1);
	if (is_nl(backup[fd]))
		return (nl_in_backup(line, &backup[fd]));
	// get_next_line 함수 안에서는 각각 독립적으로 기능도록 구현된 함수를 논리순서에 따라 호출만 하도록 작성하는것이 좋지 않을까?
	// 아래 5줄의 기능은 read_fd 함수 안으로 집어 넣는것이 구조적으로 좋아 보인다.
	// 노미네트 때문이면 어쩔 수 없지만,, -sshin
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
