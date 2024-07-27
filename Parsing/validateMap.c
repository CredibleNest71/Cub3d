/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validateMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:34:07 by mresch            #+#    #+#             */
/*   Updated: 2024/07/27 14:00:17 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_vert(const char *checkme)
{
	int	i;

	i = 0;
	while (checkme[i])
	{
		if (!is_char(checkme[i], "1 "))
			return (1);
		i++;
	}
	return (0);
}

int	check_walls(char **map, t_game *g)
{
	char	*checkme;
	int		i;

	i = 0;
	while (map[i])
	{
		checkme = ft_strtrim(map[i], " ");
		if (!checkme)
			return (1);
		if (checkme[0] != '1' || checkme[ft_strlen(checkme) - 1] != '1')
			return (free_and_null((void **)&checkme), 1);
		if (!i || i == g->map_height - 1)
			if (check_vert(checkme))
				return (free_and_null((void **)&checkme), 1);
		free_and_null((void **)&checkme);
		i++;
	}
	return (0);
}

int	check_surrounding(char **map, int x, int y, t_game *g)
{
	if ((x && !is_char(map[y][x - 1], " 1")) ||
		(x < g->map_width - 1 && !is_char(map[y][x + 1], " 1")) ||
		(y && !is_char(map[y - 1][x], " 1")) ||
		(y < g->map_height - 2 && !is_char(map[y + 1][x], " 1")) /*|| 
		(y && x && !is_char(map[y - 1][x - 1], " 1")) || 
		(y < g->map_height - 2 && x && !is_char(map[y + 1][x - 1], " 1")) ||
		(y && x < g->map_width - 1 && !is_char(map[y - 1][x + 1], " 1")) || 
		(x < g->map_width - 1 && y < g->map_height - 2 && !is_char(map[y + 1][x
				+ 1], " 1"))*/)
		return (1);
	return (0);
}

int	check_spaces(char **map, t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				if (check_surrounding(map, x, y, g))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(char **map, t_game *g)
{
	if (!map)
		return (ft_putendl_fd("No map\n", STDERR_FILENO), 1);
	if (check_player(map, g))
		return (1);
	if (check_walls(map, g))
		return (1);
	if (check_spaces(map, g))
		return (1);
	return (0);
}
