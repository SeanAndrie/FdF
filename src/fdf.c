/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:02:21 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/05 14:46:28 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	error(char *type, char *message)
{
	ft_putstr_fd("FdF: ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	exit(1);
}

void	print_grid(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	ft_printf("Shape: (%d, %d)\n", map->x_dim, map->y_dim);
	ft_printf("{\n");
	while (y < map->y_dim)
	{
		ft_printf("\t[ ");
		x = 0;
		while (x < map->x_dim)
		{
			ft_printf("%3d ", map->grid[y][x]);
			x++;
		}
		ft_printf(" ]\n");
		y++;
	};
	ft_printf("}\n");
}

void	print_point_params(t_map *map, int y, int x)
{
	printf("\nPoint Params:\n");
	printf("x: %f\n", map->grid[y][x].x);
	printf("y: %f\n", map->grid[y][x].y);
	printf("z: %i\n", map->grid[y][x].z);
	printf("color (raw): %d\n", map->grid[y][x].color);
	printf("trgb: ");
	printf("(%d, %d, %d, %d)\n\n", 
		get_color_param(map->grid[y][x].color, T),
		get_color_param(map->grid[y][x].color, R),
		get_color_param(map->grid[y][x].color, G),
		get_color_param(map->grid[y][x].color, B)
	);
}

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac < 2)
	{
		error("Usage", "./fdf <filename>.fdf  or  path/to/<filename>.fdf");
		return (1);
	}
	map = create_map(av[1]);

	ft_printf("Map Dimensions: (%d, %d)\n", map->x_dim, map->y_dim);

	print_point_params(map, 2, 3);

	cleanup_grid(map->grid, map->y_dim);
	free(map);
	return (0);
}
