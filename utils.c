/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:26:32 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/27 16:21:09 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	convert_color(int rgb[])
{
	unsigned int	ret;

	ret = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (ret);
}

void	print_err(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	exit(1);
}

char	*cub_strtrim(char *s1, char *set)
{
	char	*res;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (ft_strlen(s1) == 0)
	{
		free(s1);
		return (ft_strdup(""));
	}
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= 0 && ft_strchr(set, s1[end]))
	{
		if (end == 0)
			break ;
		end--;
	}
	if (start > end)
	{
		free(s1);
		return (ft_strdup(""));
	}
	res = ft_substr(s1, start, end - start + 1);
	free(s1);
	return (res);
}
