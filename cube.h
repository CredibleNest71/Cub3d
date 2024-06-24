/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:48:05 by mresch            #+#    #+#             */
/*   Updated: 2024/06/24 16:00:04 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

# include <stdio.h>
# include <math.h>

# include "Extras/extras.h"
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include "Movement/movement.h"

# define PI	3.1415926536

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

#endif
