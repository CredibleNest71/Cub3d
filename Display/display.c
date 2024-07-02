/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:15:07 by mresch            #+#    #+#             */
/*   Updated: 2024/07/02 14:27:29 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#define COLOR1 7162376
#define COLOR2 1234
#define COLOR3 1234231

t_info	create_buffer(t_game *g)
{
	t_info	info;
	
	info.image = mlx_new_image(g->minilibx.mlx, g->minilibx.screen_width, g->minilibx.screen_height);
	info.buf = mlx_get_data_addr(info.image, &info.bits_per_pixel,\
				&info.line_bytes, &info.endian);
	return (info);
}

void	draw_single_line(t_game *g, t_ray *ray, t_info info)
{
	int	pixel;
	int	y;
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int) ((1 / ray->dist) * g->minilibx.screen_height);
	draw_start = g->minilibx.screen_height / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = g->minilibx.screen_height / 2 + line_height / 2;
	y = -1;
	while (++y < draw_start && y < g->minilibx.screen_height)
	{
		pixel = (ray->num * 4) + (y * info.line_bytes);
		colorize(&info.buf[pixel], COLOR1, info.endian);
	}
	while (++y < draw_end && y < g->minilibx.screen_height)
	{
		pixel = (ray->num * 4) + (y * info.line_bytes);
		colorize(&info.buf[pixel], COLOR2, info.endian);
	}
	while (++y < g->minilibx.screen_height && y < g->minilibx.screen_height)
	{
		pixel = (ray->num * 4) + (y * info.line_bytes);
		colorize(&info.buf[pixel], COLOR3, info.endian);
	}
}

void	display(t_game *g, t_ray *rays)
{
	int	x;
	t_info info;

	info = create_buffer(g);
	x = 0;
	while (x < g->minilibx.screen_width)
	{
		draw_single_line(g, &rays[x], info);
		x++;
	}
	mlx_put_image_to_window(g->minilibx.mlx, g->minilibx.window, info.image, 0, 0);
}
