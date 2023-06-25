/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:36:21 by yham              #+#    #+#             */
/*   Updated: 2023/06/25 22:21:19 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_newline_idx(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*update_keep(char **p_keep, int total_len, int len)
{
	char	*res;
	char	*next_keep;

	if (total_len == len || len == 0)
	{
		res = gnl_strdup(*p_keep);
		free(*p_keep);
		*p_keep = NULL;
		return (res);
	}
	next_keep = gnl_strdup(*p_keep + len);
	(*p_keep)[len] = '\0';
	res = gnl_strdup(*p_keep);
	free(*p_keep);
	*p_keep = next_keep;
	return (res);
}

static void	empty_keep(char **p_keep)
{
	free(*p_keep);
	*p_keep = NULL;
}

char	*get_next_line(int fd)
{
	int			n_idx;
	int			buf_size;
	static char	*keep[OPEN_MAX];
	char		buf[10000 + 1];

	if (fd < 0)
		return (NULL);
	n_idx = -1;
	while (n_idx < 0)
	{
		buf_size = read(fd, buf, 10000);
		if (buf_size <= 0)
		{
			n_idx = get_newline_idx(keep[fd]);
			if (buf_size == -1)
				empty_keep(&(keep[fd]));
			if (buf_size == 0 || (buf_size < 0 && keep[fd]))
				break ;
			return (NULL);
		}
		buf[buf_size] = '\0';
		keep[fd] = gnl_strjoin(keep[fd], buf);
		n_idx = get_newline_idx(keep[fd]);
	}
	return (update_keep(&(keep[fd]), gnl_strlen(keep[fd]), n_idx + 1));
}
