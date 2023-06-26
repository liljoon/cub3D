/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:12:15 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 21:16:20 by isunwoo          ###   ########.fr       */
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

void	add_texture(t_cub3d_info *app, char *line, char ***wall_path, int *cnt)
{
	char	**split;

	split = ft_split(line, ' ');
	if (cnt_split(split) == 0)
		return ;
	if (cnt_split(split) != 2)
		print_err("invalid element\n");
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
	(*cnt)++;
}

void	set_player(t_cub3d_info *app, char dir, int x, int y)
{
	if (dir == 'E')
	{
		app->dir_x = 1;
		app->plane_x = 0;
		app->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		app->dir_x = -1;
		app->plane_x = 0;
		app->plane_y = -0.66;
	}
	else if (dir == 'S')
	{
		app->dir_y = 1;
		app->plane_x = -0.66;
		app->plane_y = 0;
	}
	else if (dir == 'N')
	{
		app->dir_y = -1;
		app->plane_x = 0.66;
		app->plane_y = 0;
	}
	app->player_x = x + 0.5;
	app->player_y = y + 0.5;
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
			app->map[i][j] = -1;
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
		app->map[i][j] = -1;
		j++;
	}
}

void	read_file(t_cub3d_info *app, char ***wall_path)
{
	int		i;
	int		fd;
	int		elem_cnt;
	char	*line;

	init_texture(app, wall_path);
	fd = open(app->filename, O_RDONLY);
	if (fd < 0)
		print_err("invalid file\n");
	line = get_next_line(fd);
	i = 0;
	elem_cnt = 0;
	while (line)
	{
		if (line[0] == '\n')
		{
			line = get_next_line(fd);
			continue ;
		}
		line = ft_strtrim(line, "\n");
		if (check_tex_filled(app, wall_path, elem_cnt))
		{
			if (!check_char(line, ft_strlen(line)))
				print_err("invalid map\n");
			fill_map(app, line, i);
			i++;
		}
		else
			add_texture(app, line, wall_path, &elem_cnt);
		line = get_next_line(fd);
	}
	close(fd);
	check_map_info(app);
	check_map(app);
	fill_blank(app);
}
