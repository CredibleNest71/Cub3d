/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:01:06 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/17 16:01:15 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	playerinit(int x, int y, char c, t_game *g)
{
	int		i;
	char	dirs[5] = {'E', 'N', 'W', 'S', 0};

	i = 0;
	g->player.px = x + 0.5;
	g->player.py = y + 0.5;
	while (dirs[i])
	{
		if (c == dirs[i])
			break ;
		i++;
	}
	g->player.rad = i * (PI / 2) * -1;
	g->player.fov = 60;
}

int	check_player(char **map, t_game *game)
{
	int	x;
	int	y;
	int	found;

	y = 0;
	found = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_char(map[y][x], "NEWS"))
			{
				found++;
				playerinit(x, y, map[y][x], game);
			}
			else if (!is_char(map[y][x], "01NEWS "))
				return (1);
			x++;
		}
		y++;
	}
	if (found != 1)
		return (1);
	return (0);
}
