/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:31:24 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/13 11:22:14 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;
	const char	*ret;

	p = s;
	ret = NULL;
	while (*p != '\0')
	{
		if (*p == (char)c)
			ret = p;
		p++;
	}
	if (c == '\0')
		return ((char *)p);
	else
		return ((char *)ret);
}
