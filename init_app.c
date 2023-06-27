/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:23:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/27 16:05:07 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_func(void)
{
	exit(0);
}

void	set_info(t_cub3d_info *app)
{
	char	**wall_path;
	int		i;
	int		t;

	init_map_size(app);
	wall_path = malloc(sizeof(char *) * 4);
	if (!wall_path)
		print_err("malloc error\n");
	read_file(app, &wall_path);
	app->ceiling_color = convert_color(app->ceiling);
	app->floor_color = convert_color(app->floor);
	app->pmlx = mlx_init();
	app->pmlx_win = mlx_new_window(app->pmlx, SCNWIDTH, SCNHEIGHT, "cub3D");
	app->buffer_img = mlx_new_image(app->pmlx, SCNWIDTH, SCNHEIGHT);
	i = 0;
	while (i < 4)
	{
		app->wall_textures[i] = mlx_xpm_file_to_image(\
			app->pmlx, wall_path[i], &t, &t);
		if (app->wall_textures[i] == NULL)
			print_err("invalid texture file\n");
		free(wall_path[i]);
		i++;
	}
	free(wall_path);
}

void	init_info(t_cub3d_info *app)
{
	int		i;

	app->plane_x = 0;
	app->plane_y = 0;
	app->player_x = -1;
	app->player_y = -1;
	app->dir_x = 0;
	app->dir_y = 0;
	app->map_width = 0;
	app->map_height = 0;
	app->map = NULL;
	i = 0;
	while (i < 4)
		app->player_moving[i++] = 0;
	app->player_rotating[0] = 0;
	app->player_rotating[1] = 0;
	set_info(app);
}

int	init_app(t_cub3d_info *app)
{
	init_info(app);
	mlx_loop_hook(app->pmlx, raycasting, app);
	mlx_hook(app->pmlx_win, 2, 0, set_player_move, app);
	mlx_hook(app->pmlx_win, 3, 0, unset_player_move, app);
	mlx_hook(app->pmlx_win, 17, 0, exit_func, (void *)0);
	return (0);
}
