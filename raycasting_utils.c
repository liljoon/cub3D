/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:53:37 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/27 00:53:57 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	find_wall_dir(t_cub3d_info *app, int map_y, int map_x, int side)
{
	if (map_x > app->player_x && map_y <= app->player_y)
	{
		if (side == 1)
			return (3);
		return (0);
	}
	else if (map_x <= app->player_x && map_y <= app->player_y)
	{
		if (side == 1)
			return (3);
		return (1);
	}
	else if (map_x > app->player_x && map_y > app->player_y)
	{
		if (side == 1)
			return (2);
		return (0);
	}
	else if (map_x <= app->player_x && map_y > app->player_y)
	{
		if (side == 1)
			return (2);
		return (1);
	}
	return (0);
}

unsigned int	get_color(t_cub3d_info *app, t_raycasting_info *rc, \
	int y_ratio_lineHeight, int wall_dir)
{
	int				tex_y;
	int				t;
	unsigned int	*k;

	tex_y = y_ratio_lineHeight / (double)rc->wall_height * TEXHEIGHT;
	k = (unsigned int *)mlx_get_data_addr(app->wall_textures[wall_dir], \
		&t, &t, &t);
	return (k[tex_y * TEXWIDTH + rc->tex_x]);
}

void	put_pixel_img(t_cub3d_info *app, int x, int y, unsigned int color)
{
	int				t;
	unsigned int	*img_addr;

	img_addr = (unsigned int *)mlx_get_data_addr(app->buffer_img, &t, &t, &t);
	img_addr[SCNWIDTH * y + x] = color;
}

void	draw_line(t_cub3d_info *app, t_raycasting_info *rc, \
	int screen_x, int wall_dir)
{
	int	y;
	int	draw_start;
	int	draw_end;

	draw_start = SCNHEIGHT / 2 - rc->wall_height / 2;
	draw_end = SCNHEIGHT / 2 + rc->wall_height / 2;
	y = 0;
	while (y < SCNHEIGHT)
	{
		if (y >= draw_start && y < draw_end)
			put_pixel_img(app, screen_x, y, \
				get_color(app, rc, y - draw_start, wall_dir));
		else if (y < SCNHEIGHT / 2)
			put_pixel_img(app, screen_x, y, app->ceiling_color);
		else if (y >= SCNHEIGHT / 2)
			put_pixel_img(app, screen_x, y, app->floor_color);
		y++;
	}
}
