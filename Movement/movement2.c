/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:39:19 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/24 16:38:27 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(t_player *p, t_game *g)
{
	if (check_dist(g, p->rad))
		return ;
	p->px += cos(p->rad) * p->speed;
	p->py += sin(p->rad) * p->speed;
}

void	move_backwards(t_player *p, t_game *g)
{
	if (check_dist(g, p->rad + PI))
		return ;
	p->px -= cos(p->rad) * p->speed;
	p->py -= sin(p->rad) * p->speed;
}

void	move_right(t_player *p, t_game *g)
{
	double	dir;

	dir = p->rad + PI / 2;
	if (check_dist(g, dir))
		return ;
	p->px += cos(dir) * p->speed;
	p->py += sin(dir) * p->speed;
}

void	move_left(t_player *p, t_game *g)
{
	double	dir;

	dir = p->rad - PI / 2;
	if (check_dist(g, dir))
		return ;
	p->px += cos(dir) * p->speed;
	p->py += sin(dir) * p->speed;
}
