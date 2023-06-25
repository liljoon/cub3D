/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:39:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/25 21:53:15 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/gnl.h"

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
}	t_texture;

typedef struct	s_cub3d_info
{
	char	*filename;
	void	*pmlx;
	void	*pmlx_win;
	int		screen_width;
	int		screen_heigth;
	double	planeX;
	double	planeY;
	double	player_x;
	double	player_y;
	double	dirX;
	double	dirY;

	int		map[10][10]; // 하드코딩
	t_texture	tex;
} t_cub3d_info;

int	init_app(t_cub3d_info *app);
int	raycasting(t_cub3d_info *app);

void	parse_file(t_cub3d_info *app);

char	*get_next_line(int fd);

#endif
