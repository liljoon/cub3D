/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:39:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 19:33:38 by yham             ###   ########.fr       */
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
# define screenWidth 640
# define screenHeight 480
# define texWidth 64
# define texHeight 64
# define player_move_speed 0.05
# define player_rotate_speed 0.05

typedef struct	s_cub3d_info
{
	char	*filename;
	unsigned int floor_color;
	unsigned int ceiling_color;
	void	*pmlx;
	void	*pmlx_win;
	int		screen_width;
	int		screen_heigth;
	double	planeX;
	double	planeY;
	double	player_x;
	double	player_y;
	int		player_moving[4];
	int		player_rotating;
	double	dirX;
	double	dirY;
	void	*wall_textures[4]; // 동서남북 순으로 저장
	int		floor[3];
	int		ceiling[3];
	void	*buffer_img;

	int		map_width;
	int		map_height;
	int		**map;
} t_cub3d_info;

int	init_app(t_cub3d_info *app);
int	raycasting(t_cub3d_info *app);

char	*get_next_line(int fd);

void	read_file(t_cub3d_info *app, char ***wall_path);

void	init_map_size(t_cub3d_info *app);
void	dfs_map(int curr_x, int curr_y, int **visited, t_cub3d_info *app);

int		check_tex_filled(t_cub3d_info *app, char ***wall_path, int elem_cnt);
int		check_char(char *line, int len);
void	check_map_info(t_cub3d_info *app);
int		check_wall(int x, int y, t_cub3d_info *app);
void	check_map(t_cub3d_info *app);

void	init_texture(t_cub3d_info *app, char ***wall_path);
int		cnt_split(char **split);
int		**init_visited(t_cub3d_info *app);
void	fill_blank(t_cub3d_info *app);

int set_player_move(int keycode, t_cub3d_info *app);
int unset_player_move(int keycode, t_cub3d_info *app);
void check_player_move(t_cub3d_info *app);

unsigned int convert_color(int rgb[]);
void	print_err(char *msg);

#endif
