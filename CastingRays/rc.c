/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:14:54 by mresch            #+#    #+#             */
/*   Updated: 2024/07/05 14:49:57 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	distance(double px, double py, double x, double y)
{
	double	dist;

	dist = pow(px - x, 2) + pow(py - y, 2);
	return (sqrt(dist));
}

// double	check_y(t_game *g, t_ray *ray)
// {
// 	double	y;
// 	double	x;
// 	double	d;
// 	double	dir;

// 	dir = 1;
// 	if (sin(ray->angle) < 0)
// 		dir = -dir;
// 	if (sin(ray->angle) < 0)
// 		y = floor(g->player.py);
// 	else
// 		y = ceil(g->player.py);
// 	while (1)
// 	{
// 		if (sin(ray->angle == 0))
// 			return (10) ;
// 		d = (y - g->player.py) / sin(ray->angle);
// 		x = g->player.px + (cos(ray->angle) * d);
// 		if (y < 1 || x < 1)
// 			break ;
// 		if (y > g->map_height - 2|| x > g->map_width - 2)
// 			break ;
// 		if (g->map[(int) y][(int) x] == '1')
// 			break ;
// 		y += dir;
// 	}
// 	return (distance(g->player.px, g->player.py, x, y));
// }

// double	check_x(t_game *g, t_ray *ray)
// {
// 	double	y;
// 	double	x;
// 	double	d;
// 	double	dir;

// 	dir = 1;
// 	if (cos(ray->angle) < 0)
// 		dir = -dir;
// 	if (cos(ray->angle) < 0)
// 		x = floor(g->player.px);
// 	else
// 		x = ceil(g->player.px);
// 	while (1)
// 	{
// 		if (cos(ray->angle == 0))
// 			return (10) ;
// 		d = (x - g->player.px) / cos(ray->angle);
// 		y = g->player.py + (sin(ray->angle) * d);
// 		if (y < 1 || x < 1)
// 			break ;
// 		if (y > g->map_height - 1 || x > g->map_width - 1)
// 			break ;
// 		if (g->map[(int) y][(int) x] == '1')
// 			break ;
// 		x += dir;
// 	}
// 	return (distance(g->player.px, g->player.py, x, y));
// }

double check_y(t_game *g, t_ray *ray) {
    double y, x, d, dir;

    dir = (sin(ray->angle) < 0) ? -1 : 1;
    y = (sin(ray->angle) < 0) ? floor(g->player.py) : ceil(g->player.py);
    while (1) {
        d = (y - g->player.py) / sin(ray->angle);
		if (sin(ray->angle) == 0)
			d = 1;
        x = g->player.px + cos(ray->angle) * d;
		int tempy = dir < 0 ? y - 1 : y;
        if (tempy < 0 || x < 0 || y > g->map_height - 1|| x > g->map_width - 1)
            break;
        if (g->map[(int)tempy][(int)x] == '1')
            break;
        y += dir;
    }
    return distance(g->player.px, g->player.py, x, y);
}

double check_x(t_game *g, t_ray *ray) {
    double y, x, d, dir;

    dir = (cos(ray->angle) < 0) ? -1 : 1;
    x = (cos(ray->angle) < 0) ? floor(g->player.px) : ceil(g->player.px);
    while (1) {
        d = (x - g->player.px) / cos(ray->angle);
		if (cos(ray->angle) == 0)
			d = 1;
        y = g->player.py + sin(ray->angle) * d;
		int tempx = dir < 0 ? x - 1 : x;
        if (y < 0 || tempx < 0 || y > g->map_height - 1 || x > g->map_width - 1)
            break;
        if (g->map[(int)y][(int)tempx] == '1')
            break;
        x += dir;
    }
    return distance(g->player.px, g->player.py, x, y);
}
double	cast_ray(t_game *g, t_ray *ray)
{
	double	distx;
	double	disty;
	//double	dist;

	distx = check_x(g, ray);
	disty = check_y(g, ray);
	if (distx < disty)
	{
		ray->dist = distx;
		ray->axis = cos(ray->angle) < 0 ? (enum e_dir) EA : (enum e_dir) WE;
	}
	else
	{
		ray->dist = disty;
		ray->axis = sin(ray->angle) < 0 ? (enum e_dir) NO : (enum e_dir) SO;
	}
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
	//ang_a = g->player.rad - (PI / 6);
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
