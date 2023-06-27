/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:39:20 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/27 16:34:20 by yham             ###   ########.fr       */
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
# define SCNWIDTH 640
# define SCNHEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define PLAYER_MOVE_SPEED 0.05
# define PLAYER_ROTATE_SPEED 0.05
# define PLAYER_PADDING 0.2

typedef struct s_cub3d_info
{
	char			*filename;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	void			*pmlx;
	void			*pmlx_win;
	double			plane_x;
	double			plane_y;
	double			player_x;
	double			player_y;
	int				player_moving[4];
	int				player_rotating[2];
	double			dir_x;
	double			dir_y;
	void			*wall_textures[4];
	int				floor[3];
	int				ceiling[3];
	void			*buffer_img;

	int				map_width;
	int				map_height;
	int				**map;
}	t_cub3d_info;

typedef struct s_raycasting_info
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		wall_height;
	double	wall_x;
	int		tex_x;
}	t_raycasting_info;

int				init_app(t_cub3d_info *app);
int				raycasting(t_cub3d_info *app);

int				find_wall_dir(\
	t_cub3d_info *app, int map_y, int map_x, int side);
unsigned int	get_color(\
	t_cub3d_info *app, t_raycasting_info *rc, \
	int y_ratio_lineHeight, int wall_dir);
void			put_pixel_img(\
	t_cub3d_info *app, int x, int y, unsigned int color);
void			draw_line(t_cub3d_info *app, t_raycasting_info *rc, \
	int screen_x, int wall_dir);

char			*get_next_line(int fd);

void			add_texture(t_cub3d_info *app, char *line, \
							char ***wall_path, int *cnt);
void			fill_map(t_cub3d_info *app, char *line, int i);

void			init_map_size(t_cub3d_info *app);
void			dfs_map(int curr_x, int curr_y, int **visited, \
						t_cub3d_info *app);

void			read_file(t_cub3d_info *app, char ***wall_path);

int				check_tex_filled(t_cub3d_info *app, \
								char ***wall_path, int elem_cnt);
int				check_char(char *line, int len);
void			check_map_info(t_cub3d_info *app);
int				check_wall(int x, int y, t_cub3d_info *app);
void			check_map(t_cub3d_info *app);

void			init_texture(t_cub3d_info *app, char ***wall_path);
int				cnt_split(char **split);
int				**init_visited(t_cub3d_info *app);
void			fill_blank(t_cub3d_info *app);
void			check_colors(char *colors);

int				set_player_move(int keycode, t_cub3d_info *app);
int				unset_player_move(int keycode, t_cub3d_info *app);
void			check_player_move(t_cub3d_info *app);
void			player_rotate(t_cub3d_info *app);

unsigned int	convert_color(int rgb[]);
void			print_err(char *msg);
char			*cub_strtrim(char *s1, char *set);
char			*free_and_gnl(char *line, int fd);

void			free_split(char **split);
void			free_visited(int **visited, int height);

#endif
