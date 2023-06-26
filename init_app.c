/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:23:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 18:03:26 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int exit_func(void)
{
	exit(0);
}

void init_info(t_cub3d_info *app)
{
	// 테스트용 하드코딩
	app->screen_width = screenWidth;
	app->screen_heigth = screenHeight;
	app->planeX = 0;
	app->planeY = 0;
	app->player_x = -1;
	app->player_y = -1;
	app->dirX = 0;
	app->dirY = 0;
	app->map = NULL;
	for(int i=0;i<4;i++)
		app->player_moving[i] = 0;
	app->player_rotating = 0;

	init_map_size(app);

	char **wall_path;
	wall_path = malloc(sizeof(char *) * 4);
	if (!wall_path)
		exit(1);
	read_file(app, &wall_path);

	// 나중에 변환 필요
	app->ceiling_color = 0x0099ccff;
	app->floor_color = 0x008b700c;

	app->pmlx = mlx_init();
	app->pmlx_win = mlx_new_window(app->pmlx, app->screen_width, app->screen_heigth, "cub3D");
	app->buffer_img = mlx_new_image(app->pmlx, app->screen_width, app->screen_heigth);

	int a, b;
	for (int i = 0; i < 4; i++)
		app->wall_textures[i] = mlx_xpm_file_to_image(app->pmlx, wall_path[i], &a, &b); // 하드코딩
}

int init_app(t_cub3d_info *app)
{
	init_info(app);
	mlx_loop_hook(app->pmlx, raycasting, app);
	mlx_hook(app->pmlx_win, 2, 0, set_player_move, app);
	mlx_hook(app->pmlx_win, 3, 0, unset_player_move, app);
	mlx_hook(app->pmlx_win, 17, 0, exit_func, (void *)0);
	return (0);
}
