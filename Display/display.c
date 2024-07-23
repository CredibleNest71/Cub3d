/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:15:07 by mresch            #+#    #+#             */
/*   Updated: 2024/07/19 19:23:58 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_info	*create_buffer(t_game *g)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
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

void	draw_ceil(t_game *g, t_dis *dis, int CF)
{
	int	pixel;
	int	color;
	int	end;

	if (CF)
	{
		color = g->tex.c_rgb;
		end = dis->draw_start;
	}
	else
	{
		color = g->tex.f_rgb;
		end = g->minilibx.screen_height - 1;
	}
	while (dis->y < end && dis->y < g->minilibx.screen_height - 1)
	{
		pixel = (dis->ray->num * 4) + (dis->y * dis->info->line_bytes);
		colorize(&dis->info->buf[pixel], color, dis->info->endian);
		dis->y++;
	}
}

void	*pick_tex(t_game *g, t_ray *ray)
{
	if (ray->axis == (enum e_dir)NO)
		return (g->tex.no_img);
	else if (ray->axis == (enum e_dir)EA)
		return (g->tex.ea_img);
	else if (ray->axis == (enum e_dir)SO)
	{
		ray->perc = fabs(1 - ray->perc);
		return (g->tex.so_img);
	}
	else if (ray->axis == (enum e_dir)WE)
	{
		ray->perc = fabs(1 - ray->perc);
		return (g->tex.we_img);
	}
	return (NULL);
}

void	draw_tex(t_game *g, t_dis *dis)
{
	void	*img;
	int		pixel;
	int		pixel_tex;
	t_info	info_tex;
	int		i;

	img = pick_tex(g, dis->ray);
	if (!img || (dis->ray->perc < 0 || dis->ray->perc > 1))
	{
		dis->y += dis->line_height;
		return ;
	}
	info_tex.buf = mlx_get_data_addr(img, &info_tex.bits_per_pixel,
			&info_tex.line_bytes, &info_tex.endian);
	while (dis->y < dis->draw_end && dis->y < g->minilibx.screen_height)
	{
		pixel = (dis->ray->num * 4) + (dis->y * dis->info->line_bytes);
		pixel_tex = (int)(dis->ray->perc * 479) * 4 + (int)map((t_m){dis->y,
				dis->draw_start, dis->draw_end, 10, 470}) * info_tex.line_bytes;
		i = 0;
		while (i < 4)
		{
			dis->info->buf[pixel + i] = info_tex.buf[pixel_tex + i];
			i++;
		}
		dis->y++;
	}
}

void	draw_single_line(t_game *g, t_ray *ray, t_info *info)
{
	t_dis	dis;

	dis.y = 0;
	dis.ray = ray;
	dis.info = info;
	if (!ray)
		return ;
	dis.line_height = (int)((1 / (cos(ray->angle - g->player.rad) * ray->dist)) * g->minilibx.screen_height);
	dis.draw_start = g->minilibx.screen_height / 2 - dis.line_height / 2;
	dis.draw_end = g->minilibx.screen_height / 2 + dis.line_height / 2;
	draw_ceil(g, &dis, 1);
	draw_tex(g, &dis);
	draw_ceil(g, &dis, 0);
}
