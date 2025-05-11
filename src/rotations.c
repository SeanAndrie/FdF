/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:17 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/10 03:20:23 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    apply_ortho_variations(int keycode, t_mlx_data *mlx)
{
    mlx->config.rotations = (t_point3D){0, 0, 0, 0xFF};
    mlx->config.z_scale = 0;
    if (keycode == XK_2)
        mlx->config.rotations.x = 90.0f;
    else if (keycode == XK_3)
    {
        mlx->config.rotations.x = 90.0f;
        mlx->config.rotations.z = -90.f;
    }
    redraw(mlx);
}

void    rotate_x(t_point3D *point, float angle)
{
    float y;
    float rad;

    y = point->y;
    rad = angle * M_PI / 180.0f;
    point->y = y * cos(rad) - point->z * sin(rad);
    point->z = y * sin(rad) + point->z * cos(rad);
}

void    rotate_y(t_point3D *point, float angle)
{
    float x;
    float rad;

    x = point->x;
    rad = angle * M_PI / 180.0f;
    point->x = x * cos(rad) + point->z * sin(rad);
    point->z = -x * sin(rad) + point->z *cos(rad);
}

void    rotate_z(t_point3D *point, float angle)
{
    float x;
    float rad;
    
    x = point->x;
    rad = angle * M_PI / 180.0f;
    point->x = x * cos(rad) - point->y * sin(rad);
    point->y = x * sin(rad) + point->y * cos(rad);
}

void    rotate_point(t_point3D *point, t_point3D angles)
{
    rotate_z(point, angles.z);
    rotate_y(point, angles.y);
    rotate_x(point, angles.x);
}
