/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:31:58 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 21:06:53 by yham             ###   ########.fr       */
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

int	**init_visited(t_cub3d_info *app)
{
	int	i;
	int	**visited;

	visited = malloc(sizeof(int *) * app->map_height);
	if (!visited)
		print_err("malloc error\n");
	i = 0;
	while (i < app->map_height)
	{
		visited[i] = malloc(sizeof(int) * app->map_width);
		if (!visited[i])
			print_err("malloc error\n");
		i++;
	}
	return (visited);
}

void	fill_blank(t_cub3d_info *app)
{
	int	i;
	int	j;

	i = 0;
	while (i < app->map_height)
	{
		j = 0;
		while (j < app->map_width)
		{
			if (app->map[i][j] == -1)
				app->map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	check_colors(char *colors)
{
	int	i;
	int	cnt;
	int	len;

	i = 0;
	cnt = 0;
	len = ft_strlen(colors);
	while (i < len)
	{
		if (colors[i] == ',')
			cnt++;
		if (!((colors[i] >= '0' && colors[i] <= '9') || colors[i] == ','))
			print_err("invalid element\n");
		i++;
	}
	if (cnt != 2)
		print_err("invalid element\n");
}
