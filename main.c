/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:43:49 by isunwoo           #+#    #+#             */
/*   Updated: 2023/06/26 20:47:37 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_file(char *filename)
{
	int	file_len;

	file_len = ft_strlen(filename);
	if (!(filename[file_len - 4] == '.' \
		&& filename[file_len - 3] == 'c' \
		&& filename[file_len - 2] == 'u' \
		&& filename[file_len - 1] == 'b'))
		print_err("invalid file\n");
}

int	main(int argc, char *argv[])
{
	t_cub3d_info	app;

	if (argc != 2)
		print_err("invalid argument\n");
	app.filename = argv[1];
	check_file(app.filename);
	if (init_app(&app))
		exit(0);
	mlx_loop(app.pmlx);
}
