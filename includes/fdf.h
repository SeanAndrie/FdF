/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:03:09 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/10 03:20:45 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080

# define PANEL_WIDTH WIDTH / 4

# define MAX_ZOOM 100.0f
# define MIN_ZOOM 0.8f

# define M_PI 3.14159265358979323846
# define NEG_COS_45 -0.5253219f
# define NEG_SIN_45 -0.8509035f
# define COS_30 0.8660254f
# define SIN_30 0.5f

# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_projection
{
	PROJ_ISOMETRIC,
	PROJ_ORTHOGRAPHIC,
	PROJ_CAVALIER
}						t_projection;

typedef enum e_color
{
	T = 24,
	R = 16,
	G = 8,
	B = 0
}						t_color;

typedef enum e_mouse_event
{
	MOUSE_LEFT = 1,
	MOUSE_MIDDLE = 2,
	MOUSE_SCROLLUP = 4,
	MOUSE_SCROLLDOWN = 5
}						t_mouse_event;

typedef struct s_rotation_cache{
    float cos_x, sin_x;
    float cos_y, sin_y;
    float cos_z, sin_z;
} 						t_rotation_cache;

typedef struct s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_rgb;

typedef struct s_bounds
{
	float				min_x;
	float				max_x;
	float				min_y;
	float				max_y;
}						t_bounds;

typedef struct s_point2D
{
	int					x;
	int					y;
	int					color;
}						t_point2D;

typedef struct s_point3D
{
	float				x;
	float				y;
	int					z;
	int					color;
}						t_point3D;

typedef struct s_line_params
{
	struct s_point2D	delta;
	struct s_point2D	step;
}						t_line_params;

typedef struct s_map
{
	int					x_dim;
	int					y_dim;
	struct s_point3D	**grid;
	enum e_projection	projection;
}						t_map;

typedef struct s_image
{
	void				*image;
	void				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_image;

typedef struct s_config
{
	float				scale;
	struct s_point2D	offset;
	float				z_scale;
	float				pan_speed;
	struct s_point2D	pan_start;
	int					is_panning;
	int					is_rotating;
	struct s_point3D	rotations;
	t_projection		projection;
}						t_config;

typedef struct s_mlx_data
{
	struct s_map		*map;
	struct s_config		config;
	struct s_image		map_image;
	void				*window;
	void				*connection;
}						t_mlx_data;

// Rest Config
# define XK_r 0x0072

// Rotation Mode
# define XK_Shift_L 0xffe1

// Select Orthographic Variation
# define XK_1 0x0031
# define XK_2 0x0032
# define XK_3 0x0033

// Close FdF
# define XK_Escape 0xff1b

// Switch Projection
# define XK_i 0x0069
# define XK_p 0x0070
# define XK_o 0x006f

// Zoom Adjustment
# define XK_equal 0x003d
# define XK_minus 0x002d

// Z Scale Adjustment / Map rotation
# define XK_Up 0xff52
# define XK_Down 0xff54
# define XK_Left 0xff51
# define XK_Right 0xff53

// Pan and Translation
# define XK_a 0x0061
# define XK_s 0x0073
# define XK_w 0x0077
# define XK_d 0x0064

// X11 Masks
# define ButtonPressMask 1L << 2
# define ButtonReleaseMask 1L << 3
# define PointerMotionMask 1L << 6
# define KeyPressMask 1L << 0
# define KeyReleaseMask 1L << 1
# define StructureNotifyMask 1L << 17

// X11 Events
# define ButtonPress 4
# define ButtonRelease 5
# define KeyPress 2
# define KeyRelease 3
# define MotionNotify 6
# define DestroyNotify 17

void					error(char *type, char *message, char *code);
int						close_fdf(t_mlx_data *mlx);
t_config				init_config(void);

// Hooks
int						handle_key_press(int keycode, t_mlx_data *mlx);
int						handle_key_release(int keycode, t_mlx_data *mlx);
int						handle_mouse_move(int x, int y, t_mlx_data *mlx);
int						handle_mouse_press(int button, int x, int y,
							t_mlx_data *mlx);
int						handle_mouse_release(int button, int x, int y,
							t_mlx_data *mlx);

// Hook Utilities
void					rotate_map(int keycode, t_mlx_data *mlx);
void					key_translate(int keycode, t_mlx_data *mlx);
void					adjust_scale(int button, t_mlx_data *mlx);
void					switch_projection(int keycode, t_mlx_data *mlx);
void					adjust_z_scale(int keycode, t_mlx_data *mlx,
							float factor);

// Drawing
void					draw_horizontal_lines(t_mlx_data *mlx, t_point2D offset,
							int y);
void					draw_vertical_lines(t_mlx_data *mlx, t_point2D offset,
							int x);

// Drawing Utilities
void					redraw(t_mlx_data *mlx);
t_point2D				apply_offset(t_point2D point, t_point2D offset);
int						calculate_step(int start_coord, int end_coord);
void					put_pixel_to_img(t_image *img, int x, int y, int color);
void					update_position(int *error, t_point2D *curr,
							t_line_params params);
// Rendering
void					render_map(t_mlx_data *mlx);
t_point2D				project_point(t_point3D point, t_config config);
int						render_mlx(t_mlx_data *mlx, const char *filename);
t_bounds				get_map_bounds(t_map *map, t_config config);

// Map Parser
t_map					*create_map(const char *filename);

// Map Parser Utilities
void					free_tokens(char **tokens);
int						is_hex_color(const char *token);
void					cleanup_grid(t_point3D **grid, int n_alloc);
int						get_next_trimmed(char **trimmed, int fd, char *charset);

// Rotations
void    				rotate_point(t_point3D *point, t_point3D angles);
void					apply_ortho_variations(int keycode, t_mlx_data *mlx);

// Colors
void					fill_image(t_image *img, int width, int height, unsigned int color);
t_rgb					int_to_rgb(int n);
int						get_color_param(int trgb, t_color param);
int						create_trgb(int t, int r, int g, int b);
float					calculate_interpolation(t_point2D *curr,
							t_point2D *start, t_point2D *end);

#endif
