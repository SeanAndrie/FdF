/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:24:04 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/14 13:20:17 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_and_rotate(t_point3D *point, t_config config)
{
	point->x *= config.scale;
	point->y *= config.scale;
	point->z *= config.z_scale;
	rotate_point(point, config.rotations);
}

void	reset_config(t_mlx_data *mlx)
{
	mlx->config = init_config();
	redraw(mlx);
}
