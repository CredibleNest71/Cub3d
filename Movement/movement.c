/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:19:55 by mresch            #+#    #+#             */
/*   Updated: 2024/06/26 14:33:53 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(t_player *p)
{
	p->px += cos(p->rad) * SPEED;
	p->py += sin(p->rad) * SPEED;
}
void	move_backwards(t_player *p)
{
	p->px -= cos(p->rad) * SPEED;
	p->py -= sin(p->rad) * SPEED;
}

void	move_left(t_player *p)
{
	double	dir;

	dir = p->rad + PI / 2;
	p->px += cos(dir) * SPEED;
	p->py += sin(dir) * SPEED;
}

void	move_right(t_player *p)
{
	double	dir;

	dir = p->rad - PI / 2;
	if (dir < 0)
		dir += 2 * PI;
	p->px += cos(dir) * SPEED;
	p->py += sin(dir) * SPEED;
}

void	turn_left(t_player *p)
{
	p->rad -= SPIN;
}

void	turn_right(t_player *p)
{
	p->rad += SPIN;
}
