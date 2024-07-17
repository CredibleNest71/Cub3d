/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:19:55 by mresch            #+#    #+#             */
/*   Updated: 2024/07/17 15:53:07 by mesenyur         ###   ########.fr       */
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

void	turn_left(t_player *p)
{
	p->rad = (p->rad - SPIN);
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
	if (keys.w)
		move_forward(&game->player, game);
	if (keys.s)
		move_backwards(&game->player, game);
	if (keys.a)
		move_left(&game->player, game);
	if (keys.d)
		move_right(&game->player, game);
	if (keys.left)
		turn_left(&game->player);
	if (keys.right)
		turn_right(&game->player);
	if (keys.q)
		game->player.fov -= 2;
	if (keys.e)
		game->player.fov += 2;
	return (0);
}
