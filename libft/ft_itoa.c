/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:43:01 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/18 12:53:24 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*setting(int n, int digit, int *idx)
{
	char	*res;

	if (n < 0)
	{
		res = malloc(digit + 2);
		*idx = digit + 1;
	}
	else
	{
		res = malloc(digit + 1);
		*idx = digit;
	}
	return (res);
}

static int	num_length(long long n)
{
	int	digit;

	if (n == 0)
		return (1);
	digit = 0;
	while (n != 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	long long	long_n;
	int			digit;
	char		*res;
	int			idx;

	long_n = n;
	if (long_n < 0)
		long_n *= -1;
	digit = num_length(long_n);
	res = setting(n, digit, &idx);
	if (!res)
		return (res);
	res[idx--] = '\0';
	res[idx] = '0';
	while (long_n != 0)
	{
		res[idx] = long_n % 10 + '0';
		long_n /= 10;
		idx--;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
