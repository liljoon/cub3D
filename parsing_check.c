/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:28:07 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 16:32:21 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_tex_filled(t_cub3d_info *app, char ***wall_path)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((*wall_path)[i] == NULL)
			return (0);
		if (i < 3 && (app->floor[i] == -1 || app->ceiling[i] == -1))
			return (0);
		i++;
	}
	return (1);
}

int	check_char(char *line, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!(line[i] == '0' || line[i] == '1' \
			|| line[i] == 'E' || line[i] == 'W' \
			|| line[i] == 'S' || line[i] == 'N' \
			|| line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

void	check_elem(t_cub3d_info *app)
{
	if ((!app->map || app->player_x == -1 || app->player_y == -1)\
		|| (app->dirX == 0 && app->dirY == 0))
		exit(1);
}
