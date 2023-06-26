/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:29:18 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 16:30:18 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
