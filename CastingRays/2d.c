/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:09:50 by mresch            #+#    #+#             */
/*   Updated: 2024/07/17 13:35:41 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#define COLOR1 7162376
#define COLOR2 1234
#define COLOR3 1234231

// int     draw_player2d(t_game *g, t_info *info)
// {
//     int size = 50;
// 	int	pixel;

// 	for (int x = g->minilibx.screen_width / 2 - size; x < g->minilibx.screen_width / 2 + size; x++){
// 		for (int y = g->minilibx.screen_height / 2 - size; x < g->minilibx.screen_height / 2 + size; y++){
// 			pixel = (x * 4) + (y * info->line_bytes);
// 			colorize(&info->buf[pixel], 0, info->endian);
// 		}
// 	}
// 	return 0;
// }

void	draw_single_ray(t_game *g, t_info *info, t_ray ray)
{
	double	px = (double)g->minilibx.screen_width / 2;
	double	py = (double)g->minilibx.screen_height / 2;
	double	curr = 0;
	int	pixel;
	while (curr < ray.dist * 100)
	{
		px = cos(ray.angle) + px;
		py = sin(ray.angle) + py;
        if (py < 0 || px < 0 || py > g->minilibx.screen_height - 1 || px > g->minilibx.screen_width - 1)
			break ;
		pixel = ((int) px * 4) + ((int)py * info->line_bytes);
		colorize(&info->buf[pixel], COLOR2, info->endian);
		curr += 1;
	}
}

// int		draw_rays(t_game *g, t_info *info)
// {
// 	t_ray	ray;
// 	double	angle = 0;
// 	while (angle < 2 * PI)
// 	{
// 		ray.angle = angle;
// 		cast_ray(g, &ray);
// 		draw_single_ray(g, info, ray);
// 		angle += PI / 180;
// 	}
// 	return 0;
// }
