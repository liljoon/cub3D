/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:57:52 by yham              #+#    #+#             */
/*   Updated: 2023/06/25 20:43:54 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_texture(t_cub3d_info *app)
{
	printf("NO : %s\n", app->tex.north);
	printf("SO : %s\n", app->tex.south);
	printf("WE : %s\n", app->tex.west);
	printf("EA : %s\n", app->tex.east);
	printf("F : %d %d %d\n", \
			app->tex.floor[0], app->tex.floor[1], app->tex.floor[2]);
	printf("C : %d %d %d\n", \
			app->tex.ceiling[0], app->tex.ceiling[1], app->tex.ceiling[2]);
}

int	main(int argc, char **argv)
{
	t_cub3d_info	app;

	if (argc != 2)
		exit(1);
	app.filename = argv[1];
	parse_file(&app);
	print_texture(&app);
}
