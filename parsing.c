/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:12:15 by yham              #+#    #+#             */
/*   Updated: 2023/06/25 21:40:03 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_texture(t_cub3d_info *app)
{
	app->tex.north = NULL;
	app->tex.south = NULL;
	app->tex.west = NULL;
	app->tex.east = NULL;
	app->tex.floor[0] = -1;
	app->tex.floor[1] = -1;
	app->tex.floor[2] = -1;
	app->tex.ceiling[0] = -1;
	app->tex.ceiling[1] = -1;
	app->tex.ceiling[2] = -1;
}

int	cnt_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	add_color(t_cub3d_info *app, char *colors, int floor)
{
	char	**color;

	color = ft_split(colors, ',');
	if (floor == 1)
	{
		app->tex.floor[0] = ft_atoi(color[0]);
		app->tex.floor[1] = ft_atoi(color[1]);
		app->tex.floor[2] = ft_atoi(color[2]);
	}
	else
	{
		app->tex.ceiling[0] = ft_atoi(color[0]);
		app->tex.ceiling[1] = ft_atoi(color[1]);
		app->tex.ceiling[2] = ft_atoi(color[2]);
	}
}

void	add_texture(t_cub3d_info *app, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (cnt_split(split) != 2)
		return ;
	if (ft_strncmp(split[0], "NO", 2) == 0)
		app->tex.north = split[1];
	else if (ft_strncmp(split[0], " SO", 2) == 0)
		app->tex.south = split[1];
	else if (ft_strncmp(split[0], "WE", 2) == 0)
		app->tex.west = split[1];
	else if (ft_strncmp(split[0], "EA", 2) == 0)
		app->tex.east = split[1];
	else if (ft_strncmp(split[0], "F", 1) == 0)
		add_color(app, split[1], 1);
	else if (ft_strncmp(split[0], "C", 1) == 0)
		add_color(app, split[1], 0);
}

int	check_tex_filled(t_cub3d_info *app)
{
	if (app->tex.north != NULL && app->tex.south != NULL \
		&& app->tex.west != NULL && app->tex.east != NULL \
		&& app->tex.floor[0] != -1 && app->tex.floor[1] != -1
		&& app->tex.floor[2] != -1 && app->tex.ceiling[0] != -1 \
		&& app->tex.ceiling[1] != -1 && app->tex.ceiling[2] != -1)
		return (1);
	return (0);
}

void	read_file(t_cub3d_info *app)
{
	int		fd;
	char	*line;

	fd = open(app->filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		add_texture(app, line);
		line = get_next_line(fd);
		if (check_tex_filled(app))
			break ;
	}
	close(fd);
}

void	parse_file(t_cub3d_info *app)
{
	init_texture(app);
	read_file(app);
}
