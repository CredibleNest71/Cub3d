/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:39:19 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/17 15:52:53 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(t_player *p, t_game *g)
{
	if (check_dist(g, p->rad))
		return ;
	p->px += cos(p->rad) * SPEED;
	p->py += sin(p->rad) * SPEED;
}

void	move_backwards(t_player *p, t_game *g)
{
	if (check_dist(g, p->rad + PI))
		return ;
	p->px -= cos(p->rad) * SPEED;
	p->py -= sin(p->rad) * SPEED;
}

void	move_right(t_player *p, t_game *g)
{
	double	dir;

	dir = p->rad + PI / 2;
	if (check_dist(g, dir))
		return ;
	p->px += cos(dir) * SPEED;
	p->py += sin(dir) * SPEED;
}

void	move_left(t_player *p, t_game *g)
{
	double	dir;

	dir = p->rad - PI / 2;
	if (check_dist(g, dir))
		return ;
	p->px += cos(dir) * SPEED;
	p->py += sin(dir) * SPEED;
}
