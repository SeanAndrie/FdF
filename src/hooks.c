/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:05:24 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/14 13:27:53 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mouse_press(int button, int x, int y, t_mlx_data *mlx)
{
	if (button == MOUSE_LEFT)
	{
		mlx->config.is_panning = 1;
		mlx->config.pan_start = (t_point2D){.x = x, .y = y};
	}
	else if (button == MOUSE_SCROLLUP || button == MOUSE_SCROLLDOWN)
		adjust_scale(button, mlx);
	redraw(mlx);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_mlx_data *mlx)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		mlx->config.is_panning = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_mlx_data *mlx)
{
	t_point2D	delta;

	if (mlx->config.is_panning)
	{
		delta.x = x - mlx->config.pan_start.x;
		delta.y = y - mlx->config.pan_start.y;
		mlx->config.offset.x += delta.x * mlx->config.pan_speed
			/ mlx->config.scale;
		mlx->config.offset.y += delta.y * mlx->config.pan_speed
			/ mlx->config.scale;
		mlx->config.pan_start = (t_point2D){x, y, 0x000000};
		redraw(mlx);
	}
	return (0);
}

int	handle_key_press(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
		return (close_fdf(mlx), 0);
	else if (keycode == XK_i || keycode == XK_p || keycode == XK_o)
		switch_projection(keycode, mlx);
	else if (keycode == XK_Shift_L)
		mlx->config.is_rotating = 1;
	else if (keycode == XK_Left || keycode == XK_Right || keycode == XK_Up
		|| keycode == XK_Down)
	{
		if (mlx->config.is_rotating)
			rotate_map(keycode, mlx);
		else
			adjust_z_scale(keycode, mlx, 0.5f);
	}
	else if (keycode == XK_w || keycode == XK_a || keycode == XK_s
		|| keycode == XK_d)
		key_translate(keycode, mlx);
	else if (keycode == XK_equal || keycode == XK_minus)
		adjust_scale(keycode, mlx);
	else if (keycode == XK_r)
		reset_config(mlx);
	else if (mlx->config.projection == PROJ_ORTHOGRAPHIC && (keycode >= XK_1
			&& keycode <= XK_3))
		apply_ortho_variations(keycode, mlx);
	return (0);
}

int	handle_key_release(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Shift_L)
		mlx->config.is_rotating = 0;
	return (0);
}
