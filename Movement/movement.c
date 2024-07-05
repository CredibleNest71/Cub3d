/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:19:55 by mresch            #+#    #+#             */
/*   Updated: 2024/07/05 17:35:39 by mresch           ###   ########.fr       */
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

int	move(t_game *game)
{
	t_keys	keys;

	keys = game->keys;
	if (keys.W)
		move_forward(&game->player, game);
	if (keys.S)
		move_backwards(&game->player, game);
	if (keys.A)
		move_left(&game->player, game);
	if (keys.D)
		move_right(&game->player, game);
	if (keys.LEFT)
		turn_left(&game->player);
	if (keys.RIGHT)
		turn_right(&game->player);
	if (keys.Q)
		game->player.fov -= 2;
	if (keys.E)
		game->player.fov += 2;
	return (0);
}
