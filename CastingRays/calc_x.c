/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:32:48 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/24 15:58:34 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	get_dir(t_ray *ray)
{
	double	dir;

	if (cos(ray->angle) < 0)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
	return (dir);
}

double	get_x(t_game *g, t_ray *ray)
{
	double	x;

	if (cos(ray->angle) < 0)
	{
		x = floor(g->player.px);
	}
	else
	{
		x = ceil(g->player.px);
	}
	return (x);
}

double	get_d(t_game *g, t_ray *ray, double x)
{
	double	d;

	d = (x - g->player.px) / cos(ray->angle);
	if (cos(ray->angle) == 0)
		d = 1;
	return (d);
}

double	check_x(t_game *g, t_ray *ray)
{
	int		tempx;
	double	y;
	double	x;
	double	d;
	double	dir;

	dir = get_dir(ray);
	x = get_x(g, ray);
	while (1)
	{
		d = get_d(g, ray, x);
		y = g->player.py + sin(ray->angle) * d;
		if (dir < 0)
			tempx = x - 1;
		else
			tempx = x;
		if (y < 0 || tempx < 0 || y > g->map_height - 1 || x > g->map_width - 1)
			break ;
		if (g->map[(int)y][(int)tempx] == '1')
			break ;
		x += dir;
	}
	ray->perc_y = y - floor(y);
	return (distance(g->player.px, g->player.py, x, y));
}
