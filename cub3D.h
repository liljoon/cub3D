/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:39:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 12:33:28 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/gnl.h"

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
	void	*wall_textures[4]; // 동서남북 순으로 저장
	int		floor[3];
	int		ceiling[3];

	int		map_width;
	int		map_height;
	int		**map;
} t_cub3d_info;

int	init_app(t_cub3d_info *app);
int	raycasting(t_cub3d_info *app);

void	init_map_size(t_cub3d_info *app);
void	read_file(t_cub3d_info *app, char ***wall_path);

char	*get_next_line(int fd);

#endif
