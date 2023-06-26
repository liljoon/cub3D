/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:38:53 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 14:33:38 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int find_wall_dir(t_cub3d_info *app, int mapY, int mapX, int side)
{
	if (mapX > app->player_x && mapY <= app->player_y) // 북동
	{
		if (side == 1) // 북
			return 3;
		else // 동
			return 0;
	}
	else if (mapX <= app->player_x && mapY < app->player_y) // 북서
	{
		if (side == 1) // 북
			return 3;
		else // 서
			return 1;
	}
	else if (mapX > app->player_x && mapY > app->player_y) // 남동
	{
		if (side == 1) // 남
			return 2;
		else // 동
			return 0;
	}
	else if (mapX <= app->player_x && mapY > app->player_y) // 남서
	{
		if (side == 1) // 남
			return 2;
		else // 서
			return 1;
	}
	return 1;
}

unsigned int get_color(t_cub3d_info *app, double lineHeight, int y_ratio_lineHeight, int texX, int wall_dir)
{
	int texY =  y_ratio_lineHeight / lineHeight * texHeight;

	int t;
	unsigned int *k = (unsigned int *)mlx_get_data_addr(app->wall_textures[wall_dir], &t, &t, &t);

	return (k[texY * texWidth + texX]);
}

void put_pixel_img(t_cub3d_info *app, int x, int y, unsigned int color)
{
	int t;
	unsigned int *img_addr = (unsigned int *)mlx_get_data_addr(app->buffer_img, &t, &t, &t);

	img_addr[app->screen_width * y + x] = color;
}

void draw_line(t_cub3d_info *app, int screen_x, double wall_height, int texX, int wall_dir)
{
	int	y;
	int draw_start;
	int draw_end;

	draw_start = app->screen_heigth / 2 - wall_height / 2;
	draw_end = app->screen_heigth / 2 + wall_height / 2;

	y = 0;
	while (y < app->screen_heigth)
	{
		if (y >= draw_start && y < draw_end)
			put_pixel_img(app, screen_x, y, get_color(app, wall_height, y - draw_start, texX, wall_dir));
		else if (y < app->screen_heigth / 2)
			put_pixel_img(app, screen_x, y, app->ceiling);
		else if (y >= app->screen_heigth / 2)
			put_pixel_img(app, screen_x, y, app->floor);
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

//texture
	double wallX; // where exactly the wall was hit
	if (side == 0)
		wallX = app->player_y + perpWallDist * rayDirY;
	else
		wallX = app->player_x + perpWallDist * rayDirX;
	wallX -= floor((wallX));

	// x coordinate on the texture
	int texX = (int)(wallX * (double)(texWidth));
	if (side == 0 && rayDirX > 0)
		texX = texWidth - texX - 1;
	if (side == 1 && rayDirY < 0)
		texX = texWidth - texX - 1;

//end

	draw_line(app, ray_count, wall_height, texX, find_wall_dir(app, mapY, mapX, side));
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
	mlx_put_image_to_window(app->pmlx, app->pmlx_win, app->buffer_img, 0, 0);
	return (0);
}
