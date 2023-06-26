/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:26:32 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 18:48:00 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	convert_color(int rgb[])
{
	unsigned int	ret;

	ret = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (ret);
}