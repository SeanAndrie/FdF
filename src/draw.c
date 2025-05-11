/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 02:47:05 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/10 00:59:29 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_line_params init_line_params(t_point2D start, t_point2D end)
{
	t_line_params params;

	params.delta.x = abs(end.x - start.x);
	params.delta.y = abs(end.y - start.y);
	params.step.x = calculate_step(start.x, end.x);
	params.step.y = calculate_step(start.y, end.y);
	return (params);
}

static int	calculate_gradient(t_point2D *curr, t_point2D *start, t_point2D *end)
{
	t_rgb	color_start;
	t_rgb	color_curr;
	t_rgb	color_end;
	float	t;

	color_start = int_to_rgb(start->color);
	color_end = int_to_rgb(end->color);
	t = calculate_interpolation(curr, start, end);
	color_curr.r = (unsigned char)(color_start.r + (color_end.r - color_start.r)
			* t);
	color_curr.g = (unsigned char)(color_start.g + (color_end.g - color_start.g)
			* t);
	color_curr.b = (unsigned char)(color_start.b + (color_end.b - color_start.b)
			* t);
	return (create_trgb(0xFF, color_curr.r, color_curr.g, color_curr.b));
}

static int draw_line(t_image *img, t_point2D start, t_point2D end)
{
	t_point2D		curr;
	int				error;
	t_line_params	params;

	curr = start;
	params = init_line_params(start, end);
	error = params.delta.x - params.delta.y;
	while (1)
	{
		put_pixel_to_img(img, curr.x, curr.y, calculate_gradient(&curr, &start,
				&end));
		if (curr.x == end.x && curr.y == end.y)
			break ;
		update_position(&error, &curr, params);
	}
	return (1);
}

void	draw_horizontal_lines(t_mlx_data *mlx, t_point2D offset, int y)
{
	int			x;
	t_image		*img;
	t_map		*map;
	t_config	config;
	t_point2D	segments[2];

	map = mlx->map;
	x = map->x_dim - 1;
	config = mlx->config;
	img = &mlx->map_image;
	while (x--)
	{
		segments[0] = apply_offset(project_point(map->grid[y][x], config),
				offset);
		segments[1] = apply_offset(project_point(map->grid[y][x + 1], config),
				offset);
		if (!draw_line(img, segments[0], segments[1]))
			close_fdf(mlx);
	}
}

void	draw_vertical_lines(t_mlx_data *mlx, t_point2D offset, int x)
{
	int			y;
	t_image		*img;
	t_map		*map;
	t_config	config;
	t_point2D	segments[2];

	map = mlx->map;
	y = map->y_dim - 1;
	config = mlx->config;
	img = &mlx->map_image;
	while (y--)
	{
		segments[0] = apply_offset(project_point(map->grid[y][x], config),
				offset);
		segments[1] = apply_offset(project_point(map->grid[y + 1][x], config),
				offset);
		if (!draw_line(img, segments[0], segments[1]))
			close_fdf(mlx);
	}
}
