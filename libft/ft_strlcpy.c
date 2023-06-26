/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 16:11:07 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/21 16:24:17 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	idx;

	idx = 0;
	if (size != 0)
	{
		while (idx < size - 1 && src[idx] != '\0')
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = '\0';
	}
	while (src[idx] != '\0')
		idx++;
	return (idx);
}
