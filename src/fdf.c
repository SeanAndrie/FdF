/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:02:21 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/14 13:21:21 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	error(char *type, char *message, char *code)
{
	ft_putstr_fd("FdF: ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	if (code)
		exit(ft_atoi(code));
}

int	close_fdf(t_mlx_data *mlx)
{
	if (mlx->connection)
	{
		if (mlx->window)
			mlx_destroy_window(mlx->connection, mlx->window);
		if (mlx->map_image.image)
			mlx_destroy_image(mlx->connection, mlx->map_image.image);
		mlx_destroy_display(mlx->connection);
		free(mlx->connection);
	}
	if (mlx->map)
	{
		cleanup_grid(mlx->map->grid, mlx->map->y_dim);
		free(mlx->map);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

t_config	init_config(void)
{
	t_config	def;

	def.scale = 8.0f;
	def.z_scale = 2.0f;
	def.is_panning = 0;
	def.is_rotating = 0;
	def.pan_speed = 8.0;
	def.projection = PROJ_ISOMETRIC;
	def.offset = (t_point2D){.x = 0, .y = 0};
	def.pan_start = (t_point2D){.x = 0, .y = 0};
	def.rotations = (t_point3D){.x = 0, .y = 0, .z = 0};
	return (def);
}

void	setup_hooks(t_mlx_data *mlx)
{
	mlx_hook(mlx->window, KeyPress, KeyPressMask, handle_key_press, mlx);
	mlx_hook(mlx->window, KeyRelease, KeyReleaseMask, handle_key_release, mlx);
	mlx_hook(mlx->window, ButtonPress, ButtonPressMask, handle_mouse_press,
		mlx);
	mlx_hook(mlx->window, ButtonRelease, ButtonReleaseMask,
		handle_mouse_release, mlx);
	mlx_hook(mlx->window, MotionNotify, PointerMotionMask, handle_mouse_move,
		mlx);
	mlx_hook(mlx->window, DestroyNotify, 0, close_fdf, mlx);
}

int	main(int ac, char **av)
{
	t_mlx_data	mlx;

	if (ac < 2 || !ft_strchr(av[1], '.'))
		error("Usage", "./fdf <filename>.fdf  or  path/to/<filename>.fdf", "1");
	mlx.config = init_config();
	if (!render_mlx(&mlx, av[1]))
		error("MLX", "Failed to initialize MLX.", "1");
	setup_hooks(&mlx);
	mlx_do_key_autorepeaton(mlx.connection);
	mlx_loop(mlx.connection);
	close_fdf(&mlx);
	return (0);
}
