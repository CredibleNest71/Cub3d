/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:15:07 by mresch            #+#    #+#             */
/*   Updated: 2024/07/16 18:03:25 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#define COLOR1 7162376
#define COLOR2 1234
#define COLOR22 123400
#define COLOR3 1234231

t_info	*create_buffer(t_game *g)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->image = NULL;
	free_and_null((void **)&info->image);
	info->image = mlx_new_image(g->minilibx.mlx, g->minilibx.screen_width,
			g->minilibx.screen_height);
	info->buf = mlx_get_data_addr(info->image, &info->bits_per_pixel,
			&info->line_bytes, &info->endian);
	return (info);
}

void	destroy_buffer(t_game *g, t_info *info)
{
	if (info)
	{
		if (info->image)
		{
			mlx_destroy_image(g->minilibx.mlx, info->image);
		}
		free_and_null((void **)&info);
	}
}

void	draw_ceil(t_game *g, t_info *info, t_ray *ray, int draw_start, int *og_y)
{
	int	y;
	int pixel;

	y = -1;
	while (++y < draw_start && y < g->minilibx.screen_height - 1)
	{
		pixel = (ray->num * 4) + (y * info->line_bytes);
		colorize(&info->buf[pixel], g->tex.C_rgb,
			info->endian);
	}
	*og_y = y;
}


void	draw_single_line(t_game *g, t_ray *ray, t_info *info)
{
	int	pixel;
	int	y;
	double	line_height;
	int	draw_start;
	int	draw_end;

	y = 0;
	if (!ray)
		return ;
	line_height = (int)((1 / ray->dist) * g->minilibx.screen_height);
	draw_start = (double)g->minilibx.screen_height / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (double)g->minilibx.screen_height / 2 + line_height / 2;
	draw_ceil(g, info, ray, draw_start, &y);
	while (++y < draw_end && y < g->minilibx.screen_height - 1)
	{
		pixel = (ray->num * 4) + (y * info->line_bytes);
		if (ray->axis == (enum e_dir)NO)
			colorize(&info->buf[pixel], COLOR2, info->endian);
		else if (ray->axis == (enum e_dir)EA)
			colorize(&info->buf[pixel], COLOR22 + 3000, info->endian);
		else if (ray->axis == (enum e_dir)SO)
			colorize(&info->buf[pixel], COLOR22 + 6000, info->endian);
		else if (ray->axis == (enum e_dir)WE)
			colorize(&info->buf[pixel], COLOR22 + 9000, info->endian);
	}
	while (++y < g->minilibx.screen_height - 1)
	{
		pixel = (ray->num * 4) + (y * info->line_bytes);
		colorize(&info->buf[pixel], g->tex.F_rgb,
			info->endian);
	}
}

// t_info	*display(t_game *g, t_ray *rays)
// {
// 	int		x;
// 	t_info	*info;

// 	info = create_buffer(g);
// 	x = 0;
// 	while (x < g->minilibx.screen_width)
// 	{
// 		draw_single_line(g, &rays[x], info);
// 		x++;
// 	}
// 	return (info);
// }
