/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:19:55 by mresch            #+#    #+#             */
/*   Updated: 2024/07/04 15:46:06 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#define RANGE 0.2
int	check_dist(t_game *g, double angle)
{
	t_ray	ray;
	ray.angle = angle;
	if (cast_ray(g, &ray) < RANGE)
		return (1);
	ray.angle = angle - 0.2;
	if (cast_ray(g, &ray) < RANGE)
		return (1);
	ray.angle = angle + 0.2;
	if (cast_ray(g, &ray) < RANGE)
		return (1);
	return (0);
}

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

void	turn_left(t_player *p)
{
	p->rad =  (p->rad - SPIN);
	clean_angle(&p->rad);
}

void	turn_right(t_player *p)
{
	p->rad += SPIN;
	clean_angle(&p->rad);
}
