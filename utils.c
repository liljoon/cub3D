/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:26:32 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 19:14:04 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	convert_color(int rgb[])
{
	unsigned int	ret;

	ret = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (ret);
}

void	print_err(char *msg)
{
	write(1, "Error\n", 6);
	write(1, msg, ft_strlen(msg));
	exit(1);
}
