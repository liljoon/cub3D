/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:49:14 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/21 14:42:38 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(const char *s)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
		cnt++;
	return (cnt);
}

char	*ft_strdup(const char *s1)
{
	int		s1_len;
	int		idx;
	char	*p;

	s1_len = len(s1);
	p = malloc(s1_len + 1);
	if (p == 0)
		return (p);
	idx = 0;
	while (s1[idx] != '\0')
	{
		p[idx] = s1[idx];
		idx++;
	}
	p[idx] = '\0';
	return (p);
}
