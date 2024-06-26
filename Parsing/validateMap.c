/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validateMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:34:07 by mresch            #+#    #+#             */
/*   Updated: 2024/06/26 16:46:36 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int check_player(char **map)
{
    int x;
    int y;
	int	found;

	y = 0;
	found = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_char(map[y][x], "NEWS"))
				found++;
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

int	check_vert(const char *checkme)
{
	int	i;

	i = 0;
	while (checkme[i])
	{
		if (checkme[i] != '1')
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
			return (1);
		if (!i || i == g->map_height)
			if (check_vert(checkme))
				return (1);
		free(checkme);
		i++;
	}
	
	return (0);
}

int	check_surrounding(char **map, int x, int y, t_game *g)
{
	if ((x && !is_char(map[y][x - 1], " 1")) || 
		( x < g->map_width && !is_char(map[y][x + 1], " 1")) ||
		(y && !is_char(map[y - 1][x], " 1")) ||
		(y < g->map_width && !is_char(map[y + 1][x], " 1")) ||
		(y && x && !is_char(map[y - 1][x - 1], " 1"))||
		( y < g->map_height && x && !is_char(map[y + 1][x - 1], " 1"))||
		(y && x < g->map_width && !is_char(map[y - 1][x + 1], " 1"))||
		(x < g->map_width && y < g->map_height && !is_char(map[y + 1][x + 1], " 1")))
		return (1);
	return (0);
}

int	check_spaces(char **map, t_game *g)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				if (check_surrounding(map, x, y, g))
					return (printf("x:%d; y:%d", x, y));
			x++;
		}
		y++;
	}
	return (0);
}

//1 = ERROR
//0 = CORRECT
int validate_map(char **map, t_game *g)
{
    if (check_player(map))
		return (1);
	if (check_walls(map, g))
		return (1);
	if (check_spaces(map, g))
		return (1);
	return (0);
}