/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:42:53 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/19 22:22:59 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	flag;
	int	idx;
	int	res;

	res = 0;
	idx = 0;
	flag = 0;
	while (s[idx])
	{
		if (s[idx] != c && !flag)
		{
			res++;
			flag = 1;
		}
		else if (s[idx] == c && flag)
			flag = 0;
		idx++;
	}
	return (res);
}

static int	str_len(const char *str, char c)
{
	int	idx;

	idx = 0;
	while (str[idx] != c && str[idx] != '\0')
		idx++;
	return (idx);
}

static char	*copy(char const *s, int length)
{
	char	*res;

	res = malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s, length);
	res[length] = '\0';
	return (res);
}

char	**clear_all(char **res)
{
	int	idx;

	idx = 0;
	while (res[idx])
	{
		free(res[idx]);
		idx++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words_cnt;
	char	**res;
	int		words_idx;
	int		str_idx;

	if (!s)
		return (NULL);
	words_idx = 0;
	str_idx = 0;
	words_cnt = count_words(s, c);
	res = malloc(sizeof(char *) * (words_cnt + 1));
	if (!res)
		return (res);
	while (words_idx < words_cnt)
	{
		while (s[str_idx] == c)
			str_idx++;
		res[words_idx] = copy(s + str_idx, str_len(s + str_idx, c));
		if (!res[words_idx])
			return (clear_all(res));
		str_idx += str_len(s + str_idx, c);
		words_idx++;
	}
	res[words_idx] = 0;
	return (res);
}
