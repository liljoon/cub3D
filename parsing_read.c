/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:04:22 by yham              #+#    #+#             */
/*   Updated: 2023/06/26 22:07:06 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*read_element(t_cub3d_info *app, char ***wall_path, int fd)
{
	int		elem_cnt;
	char	*line;

	line = get_next_line(fd);
	elem_cnt = 0;
	while (line)
	{
		line = ft_strtrim(line, "\n");
		if (check_tex_filled(app, wall_path, elem_cnt) && ft_strlen(line) != 0)
			break ;
		add_texture(app, line, wall_path, &elem_cnt);
		line = get_next_line(fd);
	}
	return (line);
}

void	read_map(t_cub3d_info *app, char *first_line, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = first_line;
	while (line)
	{
		line = ft_strtrim(line, "\n");
		if (ft_strlen(line) == 0)
			print_err("invalid map\n");
		if (!check_char(line, ft_strlen(line)))
			print_err("invalid map\n");
		fill_map(app, line, i++);
		line = get_next_line(fd);
	}
}

void	read_file(t_cub3d_info *app, char ***wall_path)
{
	int		fd;
	char	*map_line;

	init_texture(app, wall_path);
	fd = open(app->filename, O_RDONLY);
	if (fd < 0)
		print_err("invalid file\n");
	map_line = read_element(app, wall_path, fd);
	read_map(app, map_line, fd);
	close(fd);
	check_map_info(app);
	check_map(app);
	fill_blank(app);
}
