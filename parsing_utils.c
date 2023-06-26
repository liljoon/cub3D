/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:31:58 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 16:32:26 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_texture(t_cub3d_info *app, char ***wall_path)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		(*wall_path)[i] = NULL;
		if (i < 3)
		{
			app->floor[i] = -1;
			app->ceiling[i] = -1;
		}
		i++;
	}
}

int	cnt_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
