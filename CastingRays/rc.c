/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:14:54 by mresch            #+#    #+#             */
/*   Updated: 2024/07/02 16:38:13 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_ray	*make_rays(t_game *g)
{
	t_ray	*ret;

	ret = ft_calloc(g->minilibx.screen_width + 1, sizeof(t_ray));
	if (!ret)
		return (NULL);
	return (ret);
}


double	distance(double px, double py, double x, double y)
{
	double	dist;

	dist = pow(px - x, 2) + pow(py - y, 2);
	return (sqrt(dist));
}

double	check_y(t_game *g, t_ray *ray)
{
	double	y;
	double	x;
	double	d;
	int		dir;

	dir = 1;
	if (sin(ray->angle) < 0)
		dir = -1;
	if (sin(ray->angle) < 0)
		y = floor(g->player.py);
	else
		y = ceil(g->player.py);
	while (1)
	{
		d = (y - g->player.py) * sin(ray->angle);
		x = g->player.px + (cos(ray->angle) * d);
		if (y < 0 || x < 0)
			break ;
		if (y > g->map_height - 2 || x > g->map_width - 2)
			break ;
		if (g->map[(int) y][(int) x] == '1')
			break ;
		y += dir;
	}
	return (distance(g->player.px, g->player.py, x, y));
}

double	check_x(t_game *g, t_ray *ray)
{
	double	y;
	double	x;
	double	d;
	int		dir;

	dir = 1;
	if (cos(ray->angle) < 0)
		dir = -1;
	if (cos(ray->angle) < 0)
		x = floor(g->player.px);
	else
		x = ceil(g->player.px);
	while (1)
	{
		d = (x - g->player.px) * cos(ray->angle);
		y = g->player.py + (sin(ray->angle) * d);
		if (y < 0 || x < 0)
			break ;
		if (y > g->map_height - 2 || x > g->map_width - 2)
			break ;
		if (g->map[(int) y][(int) x] == '1')
			break ;
		x += dir;
	}
	return (distance(g->player.px, g->player.py, x, y));
}

double	cast_ray(t_game *g, t_ray *ray)
{
	double	distx;
	double	disty;
	double	dist;

	distx = check_x(g, ray);
	disty = check_y(g, ray);
	dist = distx < disty ? distx : disty;
	if (distx < disty)
		ray->axis = 1;
	ray->dist = dist;
	printf("%d", ray->axis);
	return (dist);
}

void	clean_angle(double *a)
{
	while (*a < 0)
		*a += 2 * PI;
	while (*a > 2 * PI)
		*a -= 2 * PI;
}

t_ray	*vision(t_game *g)
{
	double	ang_a;
	double	ang_b;
	double	inc;
	t_ray	*rays;
	int		count;

	rays = make_rays(g);
	if (!rays)
		return (NULL);
	ang_a = g->player.rad - (PI / 6);
	ang_b = g->player.rad + (PI / 6);
	inc = (ang_b - ang_a) / g->minilibx.screen_width;
	clean_angle(&ang_a);
	clean_angle(&ang_b);
	count = 0;
	while (count < g->minilibx.screen_width)
	{
		rays[count].angle = ang_a;
		rays[count].num = count;
		cast_ray(g, &rays[count++]);
		ang_a += inc;
	}
	return (rays);
}
