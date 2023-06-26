/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:28:07 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 18:58:04 by yham             ###   ########.fr       */
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
	if ((!app->map || app->player_x == -1 || app->player_y == -1) \
		|| (app->dirX == 0 && app->dirY == 0))
		exit(1);
}

int	check_wall(int x, int y, t_cub3d_info *app)
{
	if (!(x >= 0 && x < app->map_width \
		&& y >= 0 && y < app->map_height)
		|| app->map[y][x] == -1)
		exit(1);	// 뚫려있는 맵이라고 판단
	if (app->map[y][x] == 1)
		return (1);
	return (0);
}

void	check_map(t_cub3d_info *app)
{
	int	i;
	int	j;
	int	**visited;

	visited = init_visited(app);
	i = 0;
	while (i < app->map_height)
	{
		j = 0;
		while (j < app->map_width)
		{
			if (app->map[i][j] == 0)
				dfs_map(j, i, visited, app);
			j++;
		}
		i++;
	}
}
