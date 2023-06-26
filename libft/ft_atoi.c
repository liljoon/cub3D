/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:32:57 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/18 12:41:50 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sign(const char *str, int *idx)
{
	int	sign;

	sign = 1;
	if (str[*idx] != '\0' && (str[*idx] == '+' || str[*idx] == '-'))
	{
		if (str[*idx] == '-')
			sign *= -1;
		(*idx)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int		idx;
	int		sign;
	long	ret;

	sign = 1;
	idx = 0;
	ret = 0;
	while (str[idx] != '\0'
		&& ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32))
		idx++;
	sign = check_sign(str, &idx);
	while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
	{
		ret = ret * 10 + str[idx] - '0';
		idx++;
		if (ret > 2147483647 && sign == 1)
			return (-1);
		if (ret > 2147483648 && sign == -1)
			return (0);
	}
	return ((int)(ret * sign));
}
