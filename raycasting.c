/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:38:53 by isunwoo           #+#    #+#             */
/*   Updated: 2023/05/25 17:00:41 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(t_cub3d_info *app, int screen_x, double wall_height)
{
	int	y;

	y = 0;
	while (y < app->screen_heigth)
	{
		if (y >= app->screen_heigth / 2 - wall_height / 2 && y < app->screen_heigth / 2 + wall_height / 2)
			mlx_pixel_put(app->pmlx, app->pmlx_win, screen_x, y, 0xFF0000);
		else
			mlx_pixel_put(app->pmlx, app->pmlx_win, screen_x, y, 0x000000);
		y++;
	}
}

void ray_check(t_cub3d_info *app, int ray_count)
{
	double cameraX = 2 * ray_count / (double)app->screen_width - 1; // x-coordinate in camera space
	double rayDirX = app->dirX + app->planeX * cameraX;
	double rayDirY = app->dirY + app->planeY * cameraX;
	int mapX = (int)app->player_x;
	int mapY = (int)app->player_y;
	double sideDistX;
	double sideDistY;

	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	double perpWallDist;
	int stepX;
	int stepY;

	int hit = 0; // was there a wall hit?
	int side;	 // was a NS or a EW wall hit?
	// calculate step and initial sideDist
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (app->player_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - app->player_x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (app->player_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - app->player_y) * deltaDistY;
	}
	// perform DDA
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		// Check if ray has hit a wall
		if (app->map[mapY][mapX] > 0)
			hit = 1;
	}

	if (side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);

	int wall_height = (int)((app->screen_heigth / 2) / perpWallDist);
	draw_line(app, ray_count, wall_height);
}

int raycasting(t_cub3d_info *app)
{
	double	ray_angle;
	int		ray_count;

	ray_count = 0;
	while (ray_count < app->screen_width)
	{
		ray_check(app, ray_count);
		ray_count++;
	}
	return (0);
}
