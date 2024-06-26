/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:48:05 by mresch            #+#    #+#             */
/*   Updated: 2024/06/26 14:32:50 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include <stdbool.h>

# include "Extras/extras.h"
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include "Movement/movement.h"

# define PI	3.1415926536

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
};


typedef struct s_player
{
	double	px;		//POSITION
	double	py;
	double	rad;	//DIRECTION OF VIEW IN RADI	ANS [0 - 2PI]
}	t_player;

//contains PATH to matching texture
typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	// char	*F;
	// char	*C;
}	t_tex;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;	
}	t_mlx;

typedef struct s_game
{
	t_tex		*tex;
	t_player	*player;
	t_mlx		*mlx;
}	t_game;

void    free_and_null(void **ptr);
int 	ft_error(t_game *game, char *s);

#endif
