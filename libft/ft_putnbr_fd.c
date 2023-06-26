/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:33:39 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/12 16:07:20 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	print_recursive(int n, int fd)
{
	char	print_char;

	if (n <= 0)
	{
		return ;
	}
	else
	{
		print_recursive(n / 10, fd);
		print_char = n % 10 + '0';
		write(fd, &print_char, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		dividend;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}	
	if (n < 0)
	{
		dividend = -1 * n;
		write(fd, "-", 1);
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	else
	{
		dividend = n;
	}
	print_recursive(dividend, fd);
}
