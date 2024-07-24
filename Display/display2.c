/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:04:39 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/24 14:05:28 by mesenyur         ###   ########.fr       */
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
