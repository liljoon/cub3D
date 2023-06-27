/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:38:53 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/27 16:08:04 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray_info1(t_raycasting_info *rc, t_cub3d_info *app, int ray_count)
{
	rc->camera_x = 2 * ray_count / (double)SCNWIDTH - 1;
	rc->ray_dir_x = app->dir_x + app->plane_x * rc->camera_x;
	rc->ray_dir_y = app->dir_y + app->plane_y * rc->camera_x;
	rc->map_x = (int)app->player_x;
	rc->map_y = (int)app->player_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
}

void	init_ray_info2(t_raycasting_info *rc, t_cub3d_info *app)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (app->player_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - app->player_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (app->player_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - app->player_y) * rc->delta_dist_y;
	}
}

void	ddf(t_cub3d_info *app, t_raycasting_info *rc)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (app->map[rc->map_y][rc->map_x] > 0)
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
		rc.perp_wall_dist = (rc.side_dist_x - rc.delta_dist_x);
	else
		rc.perp_wall_dist = (rc.side_dist_y - rc.delta_dist_y);
	rc.wall_height = (int)((SCNHEIGHT / 2) / rc.perp_wall_dist);
	if (rc.side == 0)
		rc.wall_x = app->player_y + rc.perp_wall_dist * rc.ray_dir_y;
	else
		rc.wall_x = app->player_x + rc.perp_wall_dist * rc.ray_dir_x;
	rc.wall_x -= floor((rc.wall_x));
	rc.tex_x = (int)(rc.wall_x * (double)(TEXWIDTH));
	if (rc.side == 0 && rc.ray_dir_x > 0)
		rc.tex_x = TEXWIDTH - rc.tex_x - 1;
	if (rc.side == 1 && rc.ray_dir_y < 0)
		rc.tex_x = TEXWIDTH - rc.tex_x - 1;
	draw_line(app, &rc, ray_count, \
		find_wall_dir(app, rc.map_y, rc.map_x, rc.side));
}

int	raycasting(t_cub3d_info *app)
{
	int		ray_count;

	check_player_move(app);
	if (app->player_rotating[0] || app->player_rotating[1])
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
