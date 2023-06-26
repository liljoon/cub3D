/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:32:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 18:54:13 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	unset_player_move(int keycode, t_cub3d_info *app)
{
	if (keycode == 0)
		app->player_moving[0] = 0;
	else if (keycode == 1)
		app->player_moving[1] = 0;
	else if (keycode == 2)
		app->player_moving[2] = 0;
	else if (keycode == 13)
		app->player_moving[3] = 0;
	else if (keycode == 123)
		app->player_rotating = 0;
	else if (keycode == 124)
		app->player_rotating = 0;
	return (0);
}

int	set_player_move(int keycode, t_cub3d_info *app)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 0)
		app->player_moving[0] = 1;
	else if (keycode == 1)
		app->player_moving[1] = 1;
	else if (keycode == 2)
		app->player_moving[2] = 1;
	else if (keycode == 13)
		app->player_moving[3] = 1;
	else if (keycode == 123)
		app->player_rotating = -1;
	else if (keycode == 124)
		app->player_rotating = 1;
	return (0);
}

void	player_rotate(t_cub3d_info *app)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = player_rotate_speed * app->player_rotating;
	old_dir_x = app->dirX;
	app->dirX = app->dirX * cos(rot_speed) - app->dirY * sin(rot_speed);
	app->dirY = old_dir_x * sin(rot_speed) + app->dirY * cos(rot_speed);
	old_plane_x = app->planeX;
	app->planeX = app->planeX * cos(rot_speed) - app->planeY * sin(rot_speed);
	app->planeY = old_plane_x * sin(rot_speed) + app->planeY * cos(rot_speed);
}

int	check_wall_collision(int **map, double x, double y)
{
	if (map[(int)y][(int)x] == 1)
		return (1);
	return (0);
}

void	check_player_move(t_cub3d_info *app)
{
	double	old_x;
	double	old_y;

	old_x = app->player_x;
	old_y = app->player_y;
	if (app->player_moving[0])
	{
		app->player_x += app->dirY * player_move_speed;
		app->player_y -= app->dirX * player_move_speed;
	}
	if (app->player_moving[1])
	{
		app->player_x -= app->dirX * player_move_speed;
		app->player_y -= app->dirY * player_move_speed;
	}
	if (app->player_moving[2])
	{
		app->player_x -= app->dirY * player_move_speed;
		app->player_y += app->dirX * player_move_speed;
	}
	if (app->player_moving[3])
	{
		app->player_x += app->dirX * player_move_speed;
		app->player_y += app->dirY * player_move_speed;
	}
	if (check_wall_collision(app->map, app->player_x, app->player_y))
	{
		app->player_x = old_x;
		app->player_y = old_y;
	}
	if (app->player_rotating != 0)
		player_rotate(app);
}
