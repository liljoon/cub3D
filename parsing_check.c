/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:28:07 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 22:25:31 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_tex_filled(t_cub3d_info *app, char ***wall_path, int elem_cnt)
{
	int	i;

	if (elem_cnt > 6)
		print_err("invalid element\n");
	i = 0;
	while (i < 4)
	{
		if ((*wall_path)[i] == NULL)
			return (0);
		if (i < 3 && (app->floor[i] == -1 || app->ceiling[i] == -1))
			return (0);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (!(app->floor[i] >= 0 && app->floor[i] < 256)
			|| !(app->ceiling[i] >= 0 && app->ceiling[i] < 256))
			print_err("invalid element\n");
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

void	check_map_info(t_cub3d_info *app)
{
	if ((!app->map || app->player_x == -1 || app->player_y == -1) \
		|| (app->dir_x == 0 && app->dir_y == 0))
		print_err("invalid map\n");
}

int	check_wall(int x, int y, t_cub3d_info *app)
{
	if (!(x >= 0 && x < app->map_width \
		&& y >= 0 && y < app->map_height)
		|| app->map[y][x] == -1)
		print_err("invalid map\n");
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
	free_visited(visited, app->map_height);
}
