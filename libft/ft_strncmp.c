/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:41:50 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/21 16:44:17 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				idx;
	const unsigned char	*s1_u;
	const unsigned char	*s2_u;

	s1_u = (const unsigned char *)s1;
	s2_u = (const unsigned char *)s2;
	idx = 0;
	while (idx < n)
	{
		if (s1_u[idx] != s2_u[idx])
			return (s1_u[idx] - s2_u[idx]);
		else if (s1_u[idx] == '\0' && s2_u[idx] == '\0')
			return (0);
		idx++;
	}
	return (0);
}
