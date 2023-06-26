/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:44:40 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/19 17:56:22 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	idx_p;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	idx_p = 0;
	while (*s1)
	{
		p[idx_p] = *s1;
		s1++;
		idx_p++;
	}
	while (*s2)
	{
		p[idx_p] = *s2;
		s2++;
		idx_p++;
	}
	p[idx_p] = '\0';
	return (p);
}
