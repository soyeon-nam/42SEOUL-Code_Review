/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swshin <swshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:42:38 by snam              #+#    #+#             */
/*   Updated: 2021/06/17 00:47:30 by swshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// &backup[fd]로 들어온것을 fd_backup으로 선언하는것 좋은것 같다.
// 나는 char **backup으로 받았는데 fd_backup으로 구분해주는것이 더 좋은듯.
// concat_old_backup 함수는 역할이 모호하다 다른 함수를 호출하는것이 주요 기능인데 굳이 없어도 되는 함수가 아닐까?  -sshin
int			concat_old_backup(char **fd_backup, char **line, char *buf)
{
	int				flag;

	if (*fd_backup != 0)
	{
		flag = split_str(line, fd_backup);
		if (flag != 0)
		{
			free(buf); // <-
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
			free(buf); // <-
			return (-1);
		}
		**line = 0;
	}
	return (0);
}
								// line, fd_backup
char		*generate_ret_line(char **s1, char **s2)
// 여러번 사용되는 함수도 아닌데 매개변수명 맞춰주는게 이해하는데 매우매우 도움됨. -sshin
{
	char	*ret;

	if (!*s1 || !*s2)
		return (0);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(*s2) + 1));
	if (!ret)
		return (0); // 통일하지 않고 여기만 이렇게한 이유? -sshin
	ft_strncpy(ret, *s1, ft_strlen(*s1) + 1);
	ft_strlcat(ret, *s2, ft_strlen(*s1) + ft_strlen(*s2) + 1);
	// dup, join 함수를 사용하는것이 직접 복사하는 길이를 재지 않아도 되고 매개변수의 개수가 줄어들어
	// 가독성에 도움됨. -sshin
	free(*s1);
	free(*s2);
	*s2 = 0;
	return (ret);
}

int			concat_new_buf(char **line, char **fd_backup, char **buf)
{
	int flag_nl; // 다른 곳에서는 그냥 flag인데 여기만 flag_nl인 이유? -sshin

	flag_nl = split_str(fd_backup, buf);
	if (flag_nl == -1)
		return (-1);
	if (!(*line = generate_ret_line(line, fd_backup)))
	// call by pointer로 line에 할당하는것 까지 generate_ret_line 함수 안에서 했으면 어떨까
		return (-1);
	*fd_backup = *buf;
	*buf = 0;
	if (flag_nl == 0)
		return (0);
	return (1);
}
// 이해?
int			read_file(char **line, char **fd_backup, char **buf, int fd)
{
	long			read_size;
	int				ret;

	while ((read_size = read(fd, *buf, BUFFER_SIZE)) > 0)
	{
		// 버퍼를 굳이 gnl 함수 안에서 동적할당하여 가지고 들어올 필요가 있을까?
		// 괜히 버퍼를 gnl 함수에서 동적할당한 덕분에
		// 버퍼를 직접적으로 사용하지도 않는 함수 안에서 할당 해제하는것 때문에 코드 복잡해지는것 같음. -sshin
		(*buf)[read_size] = 0;
		ret = concat_new_buf(line, &fd_backup[fd], buf);
									// 이미 read_file 함수로 들어올때 fd번째 원소로 들어왔는데
									// 굳이 포인터 변수의 fd번째 원소로 작성하는것은 통일성 때문인가? -sshin
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

// libft 함수(표준이거나 빈번하게 사용되어 누구나 그 기능을 알고있는 함수)를 최대한 활용했으면
// 좀 더 이해하기 쉬운 코드가 되었을것 같음.
// 함수의 배치는 논리의 흐름에 따라 위에서 아래로 읽도록 배치하는것이 좋다고 알고있다.
// gnl 함수를 최상단에 배치하고 concat_old_backup, read_file, concat_new_buf,
// generate_ret_line 순으로 배치하는것이 좋지 않았을까. -sshin
int			get_next_line(int fd, char **line)
{
	static char		*fd_backup[OPEN_MAX];
	char			*buf;
	int				ret;

	// fd 값에 대한 예외처리를 아래와 같이 하는것 좋은것 같다!
	// 특히 두번째 인자를 따로 변수를 선언하지 않고 빈문자로 처리해서 임의의 주솟값을 가지고 오는것이 인상적 -sshin
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
