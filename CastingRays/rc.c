/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:14:54 by mresch            #+#    #+#             */
/*   Updated: 2024/07/24 17:32:27 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	cast_ray(t_game *g, t_ray *ray)
{
	double	distx;
	double	disty;

	distx = check_x(g, ray);
	disty = check_y(g, ray);
	if (distx < disty)
	{
		ray->dist = distx;
		if (cos(ray->angle) < 0)
			ray->axis = (enum e_dir)WE;
		else
			ray->axis = (enum e_dir)EA;
		ray->perc = ray->perc_y;
	}
	else
	{
		ray->dist = disty;
		if (sin(ray->angle) < 0)
			ray->axis = (enum e_dir)NO;
		else
			ray->axis = (enum e_dir)SO;
		ray->perc = ray->perc_x;
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

int	vision(t_game *g, t_info *info, bool fisheye)
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
		draw_single_line(g, &ray, info, fisheye); // 1 for fisheye 0 for without
		ang_a += inc;
		clean_angle(&ang_a);
	}
	return (0);
}
