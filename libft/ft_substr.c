/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:37:45 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/21 14:25:28 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	idx;

	if (!s)
		return (NULL);
	idx = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	while (s[start + idx] != '\0' && idx < len)
	{
		p[idx] = s[start + idx];
		idx++;
	}
	p[idx] = '\0';
	return (p);
}
