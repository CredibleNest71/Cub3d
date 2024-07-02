/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:48:05 by mresch            #+#    #+#             */
/*   Updated: 2024/07/02 14:45:02 by mresch           ###   ########.fr       */
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

enum e_MapSymbols
{
	EMPTY =		'0',
	WALL =		'1',
	PL_WEST =	'W',
	PL_EAST =	'E',
	PL_NORTH =	'N',
	PL_SOUTH =	'S',
	// ENEMY =		'X',
	// DOOR = 		'D',
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
};


typedef struct s_player
{
	double	px;		//POSITION
	double	py;
	double	rad;	//DIRECTION OF VIEW IN RADI	ANS [0 - 2PI]
}	t_player;

typedef struct s_minilibx
{
	void	*mlx;
	void	*window;
	void	*img;
	int		screen_width;
	int		screen_height;
}	t_minilibx;

typedef struct s_game
{
	t_tex		tex;
	t_player	player;
	t_minilibx	minilibx;
	char		**map;
	int			map_height;
	int			map_width;
}	t_game;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		num;
	double	stepX;
	double	stepY;
	double	angle;
	double	dist;
}	t_ray;

typedef struct imginfo
{
	int		bits_per_pixel;
	int		line_bytes;
	int		endian;
	void	*image;
	char	*buf;
}	t_info;


//display
void 	colorize(char *buffer, int color, int endian);
void	display(t_game *g, t_ray *rays);

//cleaning
void    free_and_null(void **ptr);
int 	ft_error(t_game *game, char *s);

//MAP
int 	validate_map(char **map, t_game *g);
char	**getMap(int fd, t_game *g);
void    clean_everything(t_game *game, int ret);

//initialize
void    init_game(t_game *game);
int		handle_keyboard(int button, t_game *game);
void	init_player(t_game *game);

//movement
void	move_forward(t_player *p);
void	move_backwards(t_player *p);
void	move_left(t_player *p);
void	move_right(t_player *p);
void	turn_left(t_player *p);
void	turn_right(t_player *p);

// paint in black
int	draw_player(t_game *game, double size);

//raycasting
t_ray	*vision(t_game *g);


void	init_rest(t_game *game);

int		check_player(char **map, t_game *game);



#endif
