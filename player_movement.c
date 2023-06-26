/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:32:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 17:58:47 by isunwoo          ###   ########.fr       */
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
	return (0);
}

void	check_player_move(t_cub3d_info *app)
{
	if (app->player_moving[0])
	{
		app->player_x += app->dirY * player_speed;
		app->player_y -= app->dirX * player_speed;
	}
	if (app->player_moving[1])
	{
		app->player_x -= app->dirX * player_speed;
		app->player_y -= app->dirY * player_speed;
	}
	if (app->player_moving[2])
	{
		app->player_x -= app->dirY * player_speed;
		app->player_y += app->dirX * player_speed;
	}
	if (app->player_moving[3])
	{
		app->player_x += app->dirX * player_speed;
		app->player_y += app->dirY * player_speed;
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

	if (keycode == 123 || keycode == 124)
		player_rotate(keycode, app);
	return (0);
}
