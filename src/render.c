/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:11:42 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/12 18:58:37 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point2D	project_point(t_point3D point, t_config config)
{
	t_point2D	proj;
	t_point3D	trans;

	trans = point;
	scale_and_rotate(&trans, config);
	if (config.projection == PROJ_ISOMETRIC)
	{
		proj.x = (int)roundf((trans.x - trans.y) * COS_30 + config.offset.x);
		proj.y = (int)roundf((trans.x + trans.y) * SIN_30 - trans.z
				+ config.offset.y);
	}
	else if (config.projection == PROJ_CAVALIER)
	{
		proj.x = (int)roundf((trans.x + (trans.z * NEG_COS_45))
				+ config.offset.x);
		proj.y = (int)roundf((trans.y + (trans.z * NEG_SIN_45)) - trans.z
				+ config.offset.y);
	}
	else
	{
		proj.x = (int)roundf(trans.x + config.offset.x);
		proj.y = (int)roundf(trans.y + config.offset.y);
	}
	proj.color = point.color;
	return (proj);
}

t_bounds	get_map_bounds(t_map *map, t_config config)
{
	int			x;
	int			y;
	t_point2D	proj;
	t_bounds	bounds;

	y = map->y_dim;
	bounds = (t_bounds){INFINITY, -INFINITY, INFINITY, -INFINITY};
	while (y--)
	{
		x = map->x_dim;
		while (x--)
		{
			proj = project_point(map->grid[y][x], config);
			bounds.min_x = fmin(bounds.min_x, proj.x);
			bounds.max_x = fmax(bounds.max_x, proj.x);
			bounds.min_y = fmin(bounds.min_y, proj.y);
			bounds.max_y = fmax(bounds.max_y, proj.y);
		}
	}
	return (bounds);
}

void	render_map(t_mlx_data *mlx)
{
	int			x;
	int			y;
	t_bounds	bounds;
	t_point2D	offset;

	bounds = get_map_bounds(mlx->map, mlx->config);
	offset.x = (WIDTH - (bounds.max_x - bounds.min_x)) / 2 - bounds.min_x
		+ mlx->config.offset.x;
	offset.y = (HEIGHT - (bounds.max_y - bounds.min_y)) / 2 - bounds.min_y
		+ mlx->config.offset.y;
	y = mlx->map->y_dim;
	while (y--)
		draw_horizontal_lines(mlx, offset, y);
	x = mlx->map->x_dim;
	while (x--)
		draw_vertical_lines(mlx, offset, x);
}

int	render_mlx(t_mlx_data *mlx, const char *filename)
{
	mlx->map = create_map(filename);
	if (!mlx->map)
		return (0);
	mlx->connection = mlx_init();
	if (!mlx->connection)
		return (error("Rendering", "Failed to initialize display.", NULL), 0);
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "fdf");
	if (!mlx->window)
		return (close_fdf(mlx), error("Rendering", "Failed to create window.",
				NULL), 0);
	mlx->map_image.image = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
	if (!mlx->map_image.image)
		return (close_fdf(mlx), error("Rendering", "Failed to create window.",
				NULL), 0);
	mlx->map_image.addr = mlx_get_data_addr(mlx->map_image.image,
			&mlx->map_image.bpp, &mlx->map_image.line_len,
			&mlx->map_image.endian);
	render_map(mlx);
	return (1);
}
