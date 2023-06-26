/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:23:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 19:13:15 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_func(void)
{
	exit(0);
}

void	init_info(t_cub3d_info *app)
{
	int		i;
	char	**wall_path;

	app->screen_width = SCREENWIDTH;
	app->screen_heigth = SCREENHEIGHT;
	app->planeX = 0;
	app->planeY = 0;
	app->player_x = -1;
	app->player_y = -1;
	app->dirX = 0;
	app->dirY = 0;
	app->map = NULL;
	i = 0;
	while (i < 4)
		app->player_moving[i++] = 0;
	app->player_rotating = 0;
	init_map_size(app);
	wall_path = malloc(sizeof(char *) * 4);
	if (!wall_path)
		exit(1);
	read_file(app, &wall_path);
	app->ceiling_color = convert_color(app->ceiling);
	app->floor_color = convert_color(app->floor);
	app->pmlx = mlx_init();
	app->pmlx_win = mlx_new_window(app->pmlx, app->screen_width, app->screen_heigth, "cub3D");
	app->buffer_img = mlx_new_image(app->pmlx, app->screen_width, app->screen_heigth);
	int a, b;
	i = 0;
	while (i < 4)
	{
		app->wall_textures[i] = mlx_xpm_file_to_image(app->pmlx, wall_path[i], &a, &b);
		i++;
	}
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
