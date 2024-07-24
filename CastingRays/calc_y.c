/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:06:00 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/24 15:31:12 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double 	get_dir(t_ray *ray)
{
	double	dir;
	
	if (sin(ray->angle) < 0)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
	return (dir);
}

double get_y(t_game *g, t_ray *ray)
{
	double	y;
	
	if (sin(ray->angle) < 0)
	{
		y = floor(g->player.py);
	}
	else
	{
		y = ceil(g->player.py);
	}
	return (y);
}

double get_d(t_game *g, t_ray *ray, double y)
{
	double d;
	
	d = (y - g->player.py) / sin(ray->angle);
	if (sin(ray->angle) == 0)
		d = 1;
	return (d);
}
	
double	check_y(t_game *g, t_ray *ray)
{
	int		tempy;
	double	y;
	double	x;
	double	d;
	double	dir;

	dir = get_dir(ray);
	y = get_y(g, ray);
	while (1)
	{
		d = get_d(g, ray, y);
		x = g->player.px + cos(ray->angle) * d;
		if (dir < 0)
			tempy = y - 1;
		else
			tempy = y;
		if (tempy < 0 || x < 0 || y > g->map_height - 1 || x > g->map_width - 1)
			break ;
		if (g->map[(int)tempy][(int)x] == '1')
			break ;
		y += dir;
	}
	ray->perc_x = x - floor(x);
	return (distance(g->player.px, g->player.py, x, y));
}
