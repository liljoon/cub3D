/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:12:15 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 12:32:30 by yham             ###   ########.fr       */
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

void	init_map(t_cub3d_info *app)
{
	int	i;

	app->map = malloc(sizeof(int *) * app->map_height);
	if (!(app->map))
		exit(1);
	i = 0;
	while (i < app->map_height)
	{
		app->map[i] = malloc(sizeof(int) * app->map_width);
		if (!(app->map[i]))
			exit(1);
		i++;
	}
}

void	init_map_size(t_cub3d_info *app)
{
	int		fd;
	int		line_len;
	char	*line;
	
	fd = open(app->filename, O_RDONLY);
	app->map_width = 0;
	app->map_height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			line = get_next_line(fd);
			continue ;
		}
		line = ft_strtrim(line, "\n");
		line_len = ft_strlen(line);
		if (check_char(line, line_len))
		{
			if (app->map_width < line_len)
				app->map_width = line_len;
			app->map_height++;
		}
		line = get_next_line(fd);
	}
	init_map(app);
}

void	set_player(t_cub3d_info *app, char dir, int x, int y)
{
	if (dir == 'E')
		app->dirX = 1;
	else if (dir == 'W')
		app->dirX = -1;
	else if (dir == 'S')
		app->dirY = 1;
	else if (dir == 'N')
		app->dirY = -1;
	app->player_x = x;
	app->player_y = y;
}

void	fill_map(t_cub3d_info *app, char *line, int i)
{
	int	j;

	j = 0;
	while (j < app->map_width)
	{
		if (line[j] == ' ')
			app->map[i][j] = 0;
		else if (line[j] == '0' || line[j] == '1')
			app->map[i][j] = line[j] - '0';
		else
		{
			app->map[i][j] = line[j];
			set_player(app, line[j], i, j);
		}
		j++;
	}
}

void	check_elem(t_cub3d_info *app)
{
	if ((!app->map || app->player_x == -1 || app->player_y == -1)\
		|| (app->dirX == 0 && app->dirY == 0))
		exit(1);
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
		printf("line:%s\n", line);
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

void	check_file(char *filename)
{
	int	file_len;

	file_len = ft_strlen(filename);
	if (!(filename[file_len - 4] == '.' \
		&& filename[file_len - 3] == 'c' \
		&& filename[file_len - 2] == 'u' \
		&& filename[file_len - 1] == 'b'))
	{
		printf("file error\n");
		exit(1);
	}
}