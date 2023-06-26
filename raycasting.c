/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:38:53 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 23:01:04 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray_info1(t_raycasting_info *rc, t_cub3d_info *app, int ray_count)
{
	rc->cameraX = 2 * ray_count / (double)SCNWIDTH - 1;
	rc->rayDirX = app->dir_x + app->plane_x * rc->cameraX;
	rc->rayDirY = app->dir_y + app->plane_y * rc->cameraX;
	rc->mapX = (int)app->player_x;
	rc->mapY = (int)app->player_y;
	rc->deltaDistX = fabs(1 / rc->rayDirX);
	rc->deltaDistY = fabs(1 / rc->rayDirY);
}

void	init_ray_info2(t_raycasting_info *rc, t_cub3d_info *app)
{
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (app->player_x - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - app->player_x) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (app->player_y - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - app->player_y) * rc->deltaDistY;
	}
}

void	ddf(t_cub3d_info *app, t_raycasting_info *rc)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (app->map[rc->mapY][rc->mapX] > 0)
			rc->hit = 1;
	}
}

void	ray_check(t_cub3d_info *app, int ray_count)
{
	t_raycasting_info	rc;

	init_ray_info1(&rc, app, ray_count);
	init_ray_info2(&rc, app);
	ddf(app, &rc);
	if (rc.side == 0)
		rc.perpWallDist = (rc.sideDistX - rc.deltaDistX);
	else
		rc.perpWallDist = (rc.sideDistY - rc.deltaDistY);
	rc.wall_height = (int)((SCNHEIGHT / 2) / rc.perpWallDist);
	if (rc.side == 0)
		rc.wallX = app->player_y + rc.perpWallDist * rc.rayDirY;
	else
		rc.wallX = app->player_x + rc.perpWallDist * rc.rayDirX;
	rc.wallX -= floor((rc.wallX));
	rc.texX = (int)(rc.wallX * (double)(TEXWIDTH));
	if (rc.side == 0 && rc.rayDirX > 0)
		rc.texX = TEXWIDTH - rc.texX - 1;
	if (rc.side == 1 && rc.rayDirY < 0)
		rc.texX = TEXWIDTH - rc.texX - 1;
	draw_line(app, &rc, ray_count, \
		find_wall_dir(app, rc.mapY, rc.mapX, rc.side));
}

int	raycasting(t_cub3d_info *app)
{
	int		ray_count;

	check_player_move(app);
	if (app->player_rotating != 0)
		player_rotate(app);
	ray_count = 0;
	while (ray_count < SCNWIDTH)
	{
		ray_check(app, ray_count);
		ray_count++;
	}
	mlx_put_image_to_window(app->pmlx, app->pmlx_win, app->buffer_img, 0, 0);
	return (0);
}
