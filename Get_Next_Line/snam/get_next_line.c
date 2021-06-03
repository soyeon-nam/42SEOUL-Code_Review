/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshin <sshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:42:38 by snam              #+#    #+#             */
/*   Updated: 2021/06/03 18:20:13 by sshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// &backup[fd]로 들어온것을 fd_backup으로 선언하는것 좋은것 같다.
// 나는 char **backup으로 받았는데 fd_backup으로 구분해주는것이 더 좋은듯. -sshin
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
		if (!(*line = (char *)malloc(1))) // <- line에 할당할 준비 한칸 만들고 0 넣음
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

// libft 함수(표준이거나 빈번하게 사용되어 누구나 그 기능을 알고있는 함수)를 최대한 활용했으면
// 좀 더 이해하기 쉬운 코드가 되었을것 같음.
// 함수의 배치는 논리의 흐름에 따라 위에서 아래로 읽도록 배치하는것이 좋다고 알고있다.
// gnl 함수를 최상단에 배치하고 concat_old_backup, read_file, concat_new_buf,
// generate_ret_line 순으로 배치하는것이 좋지 않았을까. -sshin
int			get_next_line(int fd, char **line)
{
	// 주관이긴 한데 변수 선언을 아래와 같이 변수 사용 순서에 따라 하는것이 가독성에 좋다고 생각함.
	// char			*buf;
	// int			ret;
	// static char	*fd_backup[OPEN_MAX]; -sshin
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
