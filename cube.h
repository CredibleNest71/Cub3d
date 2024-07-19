/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:48:05 by mresch            #+#    #+#             */
/*   Updated: 2024/07/19 14:30:01 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "GNL/get_next_line.h"
# include "Movement/movement.h"
# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# define PI 3.1415926536
# define SPAWN "NSOW"

enum			e_dir
{
	NO = 0,
	EA,
	SO,
	WE,
};

enum			e_MapSymbols
{
	EMPTY = '0',
	WALL = '1',
	PL_WEST = 'W',
	PL_EAST = 'E',
	PL_NORTH = 'N',
	PL_SOUTH = 'S',
};

enum			e_bindings
{
	ESC = 65307,
	A = 97,
	S = 115,
	D = 100,
	W = 119,
	LEFT = 65361,
	RIGHT = 65363,
	Q = 113,
	E = 101,
};
typedef struct s_m
{
	double		val;
	double		prev_min;
	double		prev_max;
	double		new_min;
	double		new_max;
}				t_m;

typedef struct s_keys
{
	int			a;
	int			s;
	int			d;
	int			w;
	int			left;
	int			right;
	int			q;
	int			e;
}				t_keys;

typedef struct s_player
{
	double		px;
	double		py;
	double		rad;
	int			fov;
}				t_player;

typedef struct s_minilibx
{
	void		*mlx;
	void		*window;
	void		*img;
	int			screen_width;
	int			screen_height;
}				t_minilibx;

typedef struct s_info
{
	int			bits_per_pixel;
	int			line_bytes;
	int			endian;
	void		*image;
	char		*buf;
	int			h;
	int			w;
}				t_info;

typedef struct s_textures
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	void		*no_img;
	void		*so_img;
	void		*we_img;
	void		*ea_img;
	int			f_rgb;
	int			c_rgb;
}				t_tex;

typedef struct s_game
{
	t_tex		tex;
	t_player	player;
	t_keys		keys;
	t_minilibx	minilibx;
	t_info		*info;
	char		**map;
	int			map_height;
	int			map_width;
}				t_game;

typedef struct s_ray
{
	int			num;
	int			axis;
	double		angle;
	double		dist;
	double		perc_x;
	double		perc_y;
	double		perc;
}				t_ray;

typedef struct s_display
{
	int			y;
	int			draw_start;
	int			draw_end;
	int			line_height;
	t_ray		*ray;
	t_info		*info;
}				t_dis;

int				get_textures(int fd, t_tex *tex, t_game *g);
void			print_map(char **map);
void			print_tex(t_tex *tex);
bool			name_check(char **av);

// display
void			colorize(char *buffer, int color, int endian);
t_info			*display(t_game *g, t_ray *rays);
void			draw_single_line(t_game *g, t_ray *ray, t_info *info);

// cleaning
void			free_and_null(void **ptr);
int				ft_error(t_game *game, char *s);

// MAP
int				validate_map(char **map, t_game *g);
char			**getMap(int fd, t_game *g);
void			clean_everything(t_game *game, int ret);

// initialize
void			init_game(t_game *game);
int				handle_keyboard(int button, t_game *game);
void			init_player(t_game *game);

// movement
void			move_forward(t_player *p, t_game *g);
void			move_backwards(t_player *p, t_game *g);
void			move_left(t_player *p, t_game *g);
void			move_right(t_player *p, t_game *g);
void			turn_left(t_player *p);
void			turn_right(t_player *p);
int				move(t_game *game);

// paint in black
int				draw_player(t_game *game, double size);

// raycasting
int				vision(t_game *g, t_info *info);
void			clean_angle(double *a);
t_info			*create_buffer(t_game *g);
double			cast_ray(t_game *g, t_ray *ray);

// TEST
int				main_display_loop_2d(t_game *g);
void			init_rest(t_game *game);
int				check_player(char **map, t_game *game);
void			free_game_tex(t_game *game);
void			destroy_buffer(t_game *g, t_info *info);
int				check_dist(t_game *g, double angle);

double			map(t_m in);
int				ft_close(t_game *game);
int				is_char(char c, char *chars);

#endif
