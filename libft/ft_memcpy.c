/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:16:38 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/14 20:26:59 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;

	if (!dst && !src)
		return (dst);
	idx = 0;
	while (idx < n)
	{
		*((unsigned char *)dst + idx) = *((unsigned char *)src + idx);
		idx++;
	}
	return (dst);
}
