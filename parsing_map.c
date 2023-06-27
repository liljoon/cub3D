/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:29:18 by yham              #+#    #+#             */
/*   Updated: 2023/06/27 16:34:52 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map(t_cub3d_info *app)
{
	int	i;

	app->map = malloc(sizeof(int *) * app->map_height);
	if (!(app->map))
		print_err("malloc error\n");
	i = 0;
	while (i < app->map_height)
	{
		app->map[i] = malloc(sizeof(int) * app->map_width);
		if (!(app->map[i]))
			print_err("malloc error\n");
		i++;
	}
}

void	init_map_size(t_cub3d_info *app)
{
	int		fd;
	int		line_len;
	char	*line;

	fd = open(app->filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		line = cub_strtrim(line, "\n");
		if (ft_strlen(line) == 0)
		{
			line = free_and_gnl(line, fd);
			continue ;
		}
		line_len = ft_strlen(line);
		if (check_char(line, line_len))
		{
			if (app->map_width < line_len)
				app->map_width = line_len;
			app->map_height++;
		}
		line = free_and_gnl(line, fd);
	}
	free(line);
	init_map(app);
}

void	dfs_map(int curr_x, int curr_y, int **visited, t_cub3d_info *app)
{
	const int	dx[4] = {0, -1, 0, 1};
	const int	dy[4] = {-1, 0, 1, 0};
	int			next_x;
	int			next_y;
	int			i;

	visited[curr_y][curr_x] = 1;
	i = 0;
	while (i < 4)
	{
		next_x = curr_x + dx[i];
		next_y = curr_y + dy[i];
		if (check_wall(next_x, next_y, app))
		{
			i++;
			continue ;
		}
		if (!visited[next_y][next_x])
			dfs_map(next_x, next_y, visited, app);
		i++;
	}
}
