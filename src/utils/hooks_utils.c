/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:38:59 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/12 01:43:01 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_map(int keycode, t_mlx_data *mlx)
{
	float	rotation_step;

	rotation_step = 1.0f;
	if (keycode == XK_Left)
		mlx->config.rotations.y -= rotation_step;
	else if (keycode == XK_Right)
		mlx->config.rotations.y += rotation_step;
	else if (keycode == XK_Up)
		mlx->config.rotations.x += rotation_step;
	else if (keycode == XK_Down)
		mlx->config.rotations.z -= rotation_step;
	mlx->config.rotations.x = fmodf(mlx->config.rotations.x, 360.0f);
	mlx->config.rotations.y = fmodf(mlx->config.rotations.y, 360.0f);
	mlx->config.rotations.z = fmodf(mlx->config.rotations.z, 360.0f);
	redraw(mlx);
}

void	key_translate(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_w)
		mlx->config.offset.y -= mlx->config.pan_speed;
	else if (keycode == XK_s)
		mlx->config.offset.y += mlx->config.pan_speed;
	else if (keycode == XK_d)
		mlx->config.offset.x += mlx->config.pan_speed;
	else if (keycode == XK_a)
		mlx->config.offset.x -= mlx->config.pan_speed;
	redraw(mlx);
}

void	switch_projection(int keycode, t_mlx_data *mlx)
{
	mlx->config.rotations = (t_point3D){0, 0, 0, 0xFF};
	if (keycode == XK_i)
		mlx->config.projection = PROJ_ISOMETRIC;
	else if (keycode == XK_o)
		mlx->config.projection = PROJ_ORTHOGRAPHIC;
	else
	{
		mlx->config.projection = PROJ_CAVALIER;
	}
	redraw(mlx);
}

void	adjust_z_scale(int keycode, t_mlx_data *mlx, float factor)
{
	if (keycode == XK_Up)
		mlx->config.z_scale += factor;
	else if (keycode == XK_Down)
		mlx->config.z_scale -= factor;
	redraw(mlx);
}

void	adjust_scale(int button, t_mlx_data *mlx)
{
	float	prev_scale;

	prev_scale = mlx->config.scale;
	if (button == MOUSE_SCROLLUP || button == XK_equal)
		mlx->config.scale = fminf(prev_scale * 1.1f, MAX_ZOOM);
	else if (button == MOUSE_SCROLLDOWN || button == XK_minus)
		mlx->config.scale = fmaxf(prev_scale * 0.9f, MIN_ZOOM);
	redraw(mlx);
}
