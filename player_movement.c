/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:32:58 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/27 16:53:18 by isunwoo          ###   ########.fr       */
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
		app->player_rotating[0] = 0;
	else if (keycode == 124)
		app->player_rotating[1] = 0;
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
		app->player_rotating[0] = 1;
	else if (keycode == 124)
		app->player_rotating[1] = 1;
	return (0);
}

void	player_rotate(t_cub3d_info *app)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = PLAYER_ROTATE_SPEED * \
		(-app->player_rotating[0] + app->player_rotating[1]);
	old_dir_x = app->dir_x;
	app->dir_x = app->dir_x * cos(rot_speed) - app->dir_y * sin(rot_speed);
	app->dir_y = old_dir_x * sin(rot_speed) + app->dir_y * cos(rot_speed);
	old_plane_x = app->plane_x;
	app->plane_x = app->plane_x * cos(rot_speed) \
		- app->plane_y * sin(rot_speed);
	app->plane_y = old_plane_x * sin(rot_speed) + app->plane_y * cos(rot_speed);
}

void	check_wall_collision(t_cub3d_info *app, double old_x, double old_y)
{
	if (app->map[(int)(app->player_y + PLAYER_PADDING)] \
		[(int)(app->player_x + PLAYER_PADDING)] == 1)
	{
		app->player_x = old_x;
		app->player_y = old_y;
	}
	else if (app->map[(int)(app->player_y - PLAYER_PADDING)] \
		[(int)(app->player_x - PLAYER_PADDING)] == 1)
	{
		app->player_x = old_x;
		app->player_y = old_y;
	}
	else if (app->map[(int)(app->player_y + PLAYER_PADDING)] \
		[(int)(app->player_x - PLAYER_PADDING)] == 1)
	{
		app->player_x = old_x;
		app->player_y = old_y;
	}
	else if (app->map[(int)(app->player_y - PLAYER_PADDING)] \
		[(int)(app->player_x + PLAYER_PADDING)] == 1)
	{
		app->player_x = old_x;
		app->player_y = old_y;
	}
}

void	check_player_move(t_cub3d_info *app)
{
	double	old_coor[2];

	old_coor[0] = app->player_x;
	old_coor[1] = app->player_y;
	if (app->player_moving[0])
	{
		app->player_x += app->dir_y * PLAYER_MOVE_SPEED;
		app->player_y -= app->dir_x * PLAYER_MOVE_SPEED;
	}
	if (app->player_moving[1])
	{
		app->player_x -= app->dir_x * PLAYER_MOVE_SPEED;
		app->player_y -= app->dir_y * PLAYER_MOVE_SPEED;
	}
	if (app->player_moving[2])
	{
		app->player_x -= app->dir_y * PLAYER_MOVE_SPEED;
		app->player_y += app->dir_x * PLAYER_MOVE_SPEED;
	}
	if (app->player_moving[3])
	{
		app->player_x += app->dir_x * PLAYER_MOVE_SPEED;
		app->player_y += app->dir_y * PLAYER_MOVE_SPEED;
	}
	check_wall_collision(app, old_coor[0], old_coor[1]);
}
