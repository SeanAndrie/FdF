/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:03:09 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/05 01:14:09 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 800
# define HEIGHT 800

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <libft.h>
# include <stdlib.h>

#define ANGLE 0.523599

typedef struct s_point2D
{
	int					x;
	int					y;
}						t_point2D;

typedef struct s_point3D
{
	float				x;
	float				y;
	int					z;
	int					color;
}						t_point3D;

typedef struct s_map
{
	int					x_dim;
	int					y_dim;
	struct s_point3D	**grid;
}						t_map;

typedef struct s_image
{
	void				*image;
	void				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_image;

typedef struct s_mlx_data
{
	void				*connection;
	void				*window;
	struct s_image		image;
}						t_mlx_data;

enum					ColorParam
{
	T = 24,
	R = 16,
	G = 8,
	B = 0
};

# define XK_Escape 0xff1b
# define XK_r 0x0072
# define XK_g 0x0067
# define XK_b 0x0062

void					error(char *type, char *message);

// Map Parsing
t_map					*create_map(const char *filename);

// Map Parsing Utilities
void					free_tokens(char **tokens);
int						is_hex_color(const char *token);
void					cleanup_grid(t_point3D **grid, int n_alloc);

// Colors
int						get_color_param(int trgb, enum ColorParam param);

#endif
