/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:46:49 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/14 13:28:53 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_position(int *error, t_point2D *curr, t_line_params params)
{
	int	doubled_error;

	doubled_error = 2 * (*error);
	if (doubled_error > -params.delta.y)
	{
		*error -= params.delta.y;
		curr->x += params.step.x;
	}
	if (doubled_error < params.delta.x)
	{
		*error += params.delta.x;
		curr->y += params.step.y;
	}
}

void	redraw(t_mlx_data *mlx)
{
	ft_bzero(mlx->map_image.addr, mlx->map_image.line_len * HEIGHT);
	render_map(mlx);
	mlx_do_sync(mlx->connection);
}

int	calculate_step(int start_coord, int end_coord)
{
	if (start_coord < end_coord)
		return (1);
	else
		return (-1);
	return (0);
}

t_point2D	apply_offset(t_point2D point, t_point2D offset)
{
	point.x += offset.x;
	point.y += offset.y;
	return (point);
}

void	put_pixel_to_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
