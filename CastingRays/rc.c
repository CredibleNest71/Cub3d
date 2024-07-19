/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:14:54 by mresch            #+#    #+#             */
/*   Updated: 2024/07/19 15:17:23 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	distance(double px, double py, double x, double y)
{
	double	dist;

	dist = pow(px - x, 2) + pow(py - y, 2);
	return (sqrt(dist));
}

double	check_y(t_game *g, t_ray *ray)
{
	int	tempy;

	double y, x, d, dir;
	dir = (sin(ray->angle) < 0) ? -1 : 1;
	y = (sin(ray->angle) < 0) ? floor(g->player.py) : ceil(g->player.py);
	while (1)
	{
		d = (y - g->player.py) / sin(ray->angle);
		if (sin(ray->angle) == 0)
			d = 1;
		x = g->player.px + cos(ray->angle) * d;
		tempy = dir < 0 ? y - 1 : y;
		if (tempy < 0 || x < 0 || y > g->map_height - 1 || x > g->map_width - 1)
			break ;
		if (g->map[(int)tempy][(int)x] == '1')
			break ;
		y += dir;
	}
	ray->perc_x = x - floor(y);
	return (distance(g->player.px, g->player.py, x, y));
}

double	check_x(t_game *g, t_ray *ray)
{
	int	tempx;

	double y, x, d, dir;
	dir = (cos(ray->angle) < 0) ? -1 : 1;
	x = (cos(ray->angle) < 0) ? floor(g->player.px) : ceil(g->player.px);
	while (1)
	{
		d = (x - g->player.px) / cos(ray->angle);
		if (cos(ray->angle) == 0)
			d = 1;
		y = g->player.py + sin(ray->angle) * d;
		tempx = dir < 0 ? x - 1 : x;
		if (y < 0 || tempx < 0 || y > g->map_height - 1 || x > g->map_width - 1)
			break ;
		if (g->map[(int)y][(int)tempx] == '1')
			break ;
		x += dir;
	}
	ray->perc_y = y - floor(y);
	return (distance(g->player.px, g->player.py, x, y));
}

double	cast_ray(t_game *g, t_ray *ray)
{
	double	distx;
	double	disty;

	distx = check_x(g, ray);
	disty = check_y(g, ray);
	if (distx < disty)
	{
		ray->dist = distx;
		ray->axis = cos(ray->angle) < 0 ? (enum e_dir)EA : (enum e_dir)WE;
		ray->perc = ray->perc_y;
	}
	else
	{
		ray->dist = disty;
		ray->axis = sin(ray->angle) < 0 ? (enum e_dir)NO : (enum e_dir)SO;
		ray->perc = ray->perc_x;
	}
	if (ray->axis == (enum e_dir) SO || ray->axis == (enum e_dir) WE)
		ray->perc = 1 - ray->perc;
	return (ray->dist);
}

void	clean_angle(double *a)
{
	while (*a < 0)
		*a += 2 * PI;
	while (*a > 2 * PI)
		*a -= 2 * PI;
}

int	vision(t_game *g, t_info *info)
{
	double	ang_a;
	double	inc;
	t_ray	ray;
	int		count;
	double	fov_rad;

	fov_rad = map((t_m){g->player.fov, 0, 360, 0, 2 * PI});
	ang_a = g->player.rad - (fov_rad / 2);
	inc = ((g->player.rad + (fov_rad / 2) - ang_a) / g->minilibx.screen_width);
	clean_angle(&ang_a);
	count = 0;
	while (count < g->minilibx.screen_width)
	{
		ray.angle = ang_a;
		ray.num = count++;
		cast_ray(g, &ray);
		draw_single_line(g, &ray, info);
		ang_a += inc;
		clean_angle(&ang_a);
	}
	return (0);
}
