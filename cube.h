/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:48:05 by mresch            #+#    #+#             */
/*   Updated: 2024/07/17 13:47:36 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include <stdbool.h>
# include <fcntl.h>

# include "Extras/extras.h"
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include "Movement/movement.h"
# include "Parsing/parsing.h"

# define PI	3.1415926536
# define SPAWN "NSOW"

enum	e_dir
{
	NO = 0,
	EA,
	SO,
	WE,
};

enum e_MapSymbols
{
	EMPTY =		'0',
	WALL =		'1',
	PL_WEST =	'W',
	PL_EAST =	'E',
	PL_NORTH =	'N',
	PL_SOUTH =	'S',
};

enum	e_bindings
{
	ESC =	65307,
	A	=	97,
	S	=	115,
	D	=	100,
	W	=	119,
	LEFT =	65361,
	RIGHT =	65363,
	Q = 113,
	E = 101,
};

typedef	struct s_keys
{
	int	a;
	int	s;
	int	d;
	int	w;
	int	left;
	int	right;
	int	q;
	int	e;
}	t_keys;

typedef struct s_player
{
	double	px;		//POSITION
	double	py;
	double	rad;	//DIRECTION OF VIEW IN RADI	ANS [0 - 2PI]
	int		fov;
}	t_player;

typedef struct s_minilibx
{
	void	*mlx;
	void	*window;
	void	*img;
	int		screen_width;
	int		screen_height;
}	t_minilibx;

typedef struct s_info
{
	int		bits_per_pixel;
	int		line_bytes;
	int		endian;
	void	*image;
	char	*buf;
}	t_info;

typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	void	*NO_img;
	void	*SO_img;
	void	*WE_img;
	void	*EA_img;
	int		F_rgb;
	int		C_rgb;
}	t_tex;

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
}	t_game;

typedef struct s_ray
{
	int		num;
	int		axis; //1 = X, 0 = Y
	double	angle;
	double	dist;
	double	perc_x;
	double	perc_y;
	double	perc;
}	t_ray;

int    get_textures(int fd, t_tex *tex, t_game *g);
void	print_map(char **map);
void	print_tex(t_tex *tex);
bool    name_check(char **av);
void	delete_map(char **map);
void	delete_tex(t_tex *tex);

//display
void	colorize(char *buffer, int color, int endian);
t_info	*display(t_game *g, t_ray *rays);
void	draw_single_line(t_game *g, t_ray *ray, t_info *info);

//cleaning
void	free_and_null(void **ptr);
int		ft_error(t_game *game, char *s);

//MAP
int		validate_map(char **map, t_game *g);
char	**getMap(int fd, t_game *g);
void	clean_everything(t_game *game, int ret);

//initialize
void	init_game(t_game *game);
int		handle_keyboard(int button, t_game *game);
void	init_player(t_game *game);

//movement
void	move_forward(t_player *p, t_game *g);
void	move_backwards(t_player *p, t_game *g);
void	move_left(t_player *p, t_game *g);
void	move_right(t_player *p, t_game *g);
void	turn_left(t_player *p);
void	turn_right(t_player *p);
int		move(t_game *game);

// paint in black
int		draw_player(t_game *game, double size);

//raycasting
int		vision(t_game *g, t_info *info);
void	clean_angle(double *a);
t_info	*create_buffer(t_game *g);
double	cast_ray(t_game *g, t_ray *ray);

//TEST
int		main_display_loop_2d(t_game *g);
void	init_rest(t_game *game);
int		check_player(char **map, t_game *game);
void	free_game_tex(t_game *game);
void	destroy_buffer(t_game *g, t_info *info);

#endif
