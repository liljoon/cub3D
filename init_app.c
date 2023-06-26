/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:23:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 12:32:12 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void player_move(int keycode, t_cub3d_info *app)
{
	if (keycode == 0)
	{
		app->player_x += app->dirY;
		app->player_y -= app->dirX;
	}
	else if (keycode == 1)
	{
		app->player_x -= app->dirX;
		app->player_y -= app->dirY;
	}
	else if (keycode == 2)
	{
		app->player_x -= app->dirY;
		app->player_y += app->dirX;
	}
	else if (keycode == 13)
	{
		app->player_x += app->dirX;
		app->player_y += app->dirY;
	}
}

void player_rotate(int keycode, t_cub3d_info *app)
{
	double rotSpeed;

	if (keycode == 123)
		rotSpeed = -0.1;
	else if (keycode == 124)
		rotSpeed = 0.1;

	double oldDirX = app->dirX;
	app->dirX = app->dirX * cos(rotSpeed) - app->dirY * sin(rotSpeed);
	app->dirY = oldDirX * sin(rotSpeed) + app->dirY * cos(rotSpeed);
	double oldPlaneX = app->planeX;
	app->planeX = app->planeX * cos(rotSpeed) - app->planeY * sin(rotSpeed);
	app->planeY = oldPlaneX * sin(rotSpeed) + app->planeY * cos(rotSpeed);
}

int key_hook(int keycode, t_cub3d_info *app)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
		player_move(keycode, app);
	if (keycode == 123 || keycode == 124)
		player_rotate(keycode, app);
	return (0);
}

int exit_func(void)
{
	exit(0);
}

void init_info(t_cub3d_info *app)
{
	// 테스트용 하드코딩
	app->screen_width = 720;
	app->screen_heigth = 480;
	app->planeX = 0;
	app->planeY = 0.66;
	app->player_x = -1;
	app->player_y = -1;
	app->dirX = 0;
	app->dirY = 0;
	app->map = NULL;

	init_map_size(app);

	char **wall_path;
	wall_path = malloc(sizeof(char *) * 4);
	if (!wall_path)
		exit(1);
	read_file(app, &wall_path);

	int a,b;
	for(int i=0; i < 4; i++)
		app->wall_textures[i] = mlx_xpm_file_to_image(app->pmlx, wall_path[i], &a, &b);

	app->pmlx = mlx_init();
	app->pmlx_win = mlx_new_window(app->pmlx, app->screen_width, app->screen_heigth, "cub3D");
}

int init_app(t_cub3d_info *app)
{
	//init_info(app);
	mlx_loop_hook(app->pmlx, raycasting, app);
	mlx_key_hook(app->pmlx_win, key_hook, app);
	mlx_hook(app->pmlx_win, 17, 0, exit_func, (void *)0);
	return (0);
}
