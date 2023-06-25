/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:29:46 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/18 12:23:24 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	idx;
	int		dt;

	if (!dst && !src)
		return (NULL);
	if (len == 0)
		return (dst);
	if (dst < src)
	{
		idx = 0;
		dt = 1;
	}
	else
	{
		idx = len - 1;
		dt = -1;
	}
	while (idx < len)
	{
		((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
		if (idx == 0 && dt == -1)
			break ;
		idx += dt;
	}
	return (dst);
}
