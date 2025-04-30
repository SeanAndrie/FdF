/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:03:09 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/30 17:20:32 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# define WIDTH 800
# define HEIGHT 800

# include <libft.h>
# include <mlx.h>

typedef struct s_image
{
    void    *image;
    void    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}               t_image;

typedef struct s_mlx_data
{
    void                *connection;
    void                *window;
    struct  s_image     image;
}               t_mlx_data;

enum ColorParam
{
    T = 24,
    R = 16,
    G = 8,
    B = 0
};

#define XK_Escape   0xff1b
#define XK_r        0x0072
#define XK_g        0x0067
#define XK_b        0x0062

int     get_color_param(int trgb, enum ColorParam param);

#endif
