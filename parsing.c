/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:12:15 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 16:31:47 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_color(t_cub3d_info *app, char *colors, int floor)
{
	char	**color;

	color = ft_split(colors, ',');
	if (floor == 1)
	{
		app->floor[0] = ft_atoi(color[0]);
		app->floor[1] = ft_atoi(color[1]);
		app->floor[2] = ft_atoi(color[2]);
	}
	else
	{
		app->ceiling[0] = ft_atoi(color[0]);
		app->ceiling[1] = ft_atoi(color[1]);
		app->ceiling[2] = ft_atoi(color[2]);
	}
}

void	add_texture(t_cub3d_info *app, char *line, char ***wall_path)
{
	char	**split;

	split = ft_split(line, ' ');
	if (cnt_split(split) == 0)
		return ;
	if (cnt_split(split) != 2)
		exit(1);
	if (ft_strncmp(split[0], "EA", 2) == 0)
		(*wall_path)[0] = split[1];
	else if (ft_strncmp(split[0], "WE", 2) == 0)
		(*wall_path)[1] = split[1];
	else if (ft_strncmp(split[0], "SO", 2) == 0)
		(*wall_path)[2] = split[1];
	else if (ft_strncmp(split[0], "NO", 2) == 0)
		(*wall_path)[3] = split[1];
	else if (ft_strncmp(split[0], "F", 1) == 0)
		add_color(app, split[1], 1);
	else if (ft_strncmp(split[0], "C", 1) == 0)
		add_color(app, split[1], 0);
}

void	set_player(t_cub3d_info *app, char dir, int x, int y)
{
	if (dir == 'E')
	{
		app->dirX = 1;
		app->planeX = 0;
		app->planeY = 0.66;
	}
	else if (dir == 'W')
	{
		app->dirX = -1;
		app->planeX = 0;
		app->planeY = -0.66;
	}
	else if (dir == 'S')
	{
		app->dirY = 1;
		app->planeX = -0.66;
		app->planeY = 0;
	}
	else if (dir == 'N')
	{
		app->dirY = -1;
		app->planeX = 0.66;
		app->planeY = 0;
	}
	app->player_x = x;
	app->player_y = y;
}

void	fill_map(t_cub3d_info *app, char *line, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(line);
	while (j < len)
	{
		if (line[j] == ' ')
			app->map[i][j] = 0;
		else if (line[j] == '0' || line[j] == '1')
			app->map[i][j] = line[j] - '0';
		else if (line[j] == 'E' || line[j] == 'W' \
				|| line[j] == 'S' || line[j] == 'N')
		{
			app->map[i][j] = 0;
			set_player(app, line[j], j, i);
		}
		j++;
	}
	while (j < app->map_width)
	{
		app->map[i][j] = 0;
		j++;
	}
}

void	read_file(t_cub3d_info *app, char ***wall_path)
{
	int		i;
	int		fd;
	char	*line;

	init_texture(app, wall_path);
	fd = open(app->filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (line[0] == '\n')
		{
			line = get_next_line(fd);
			continue ;
		}
		line = ft_strtrim(line, "\n");
		if (check_tex_filled(app, wall_path))
		{
			if (!check_char(line, ft_strlen(line)))
				exit(1);
			fill_map(app, line, i);
			i++;
		}
		else
			add_texture(app, line, wall_path);
		line = get_next_line(fd);
	}
	close(fd);
	check_elem(app);
}
