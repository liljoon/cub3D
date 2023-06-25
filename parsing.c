/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:12:15 by yham              #+#    #+#             */
/*   Updated: 2023/06/25 22:49:14 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_texture(t_cub3d_info *app, char **wall_path)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		*wall_path[i] = NULL;
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

void	add_texture(t_cub3d_info *app, char *line, char **wall_path)
{
	char	**split;

	split = ft_split(line, ' ');
	if (cnt_split(split) != 2)
		return ;
	if (ft_strncmp(split[0], "EA", 2) == 0)
		*wall_path[0] = ft_strtrim(split[1], "\n");
	else if (ft_strncmp(split[0], "WE", 2) == 0)
		*wall_path[1] = ft_strtrim(split[1], "\n");
	else if (ft_strncmp(split[0], " SO", 2) == 0)
		*wall_path[2] = ft_strtrim(split[1], "\n");
	else if (ft_strncmp(split[0], "NO", 2) == 0)
		*wall_path[3] = ft_strtrim(split[1], "\n");
	else if (ft_strncmp(split[0], "F", 1) == 0)
		add_color(app, split[1], 1);
	else if (ft_strncmp(split[0], "C", 1) == 0)
		add_color(app, split[1], 0);
}

int	check_tex_filled(t_cub3d_info *app, char **wall_path)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (*wall_path[i] == NULL \
			|| (i < 3 && app->floor[i] == -1 && app->ceiling[i] == -1))
			return (0);
		i++;
	}
	return (1);
}

void	read_file(t_cub3d_info *app, char **wall_path)
{
	int		fd;
	char	*line;

	fd = open(app->filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		add_texture(app, line, wall_path);
		line = get_next_line(fd);
		if (check_tex_filled(app, wall_path) == 1)
			break ;
	}
	close(fd);
}
