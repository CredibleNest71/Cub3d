/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validateMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:34:07 by mresch            #+#    #+#             */
/*   Updated: 2024/07/04 14:16:41 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	playerinit(int x, int y, char c, t_game *g)
{
	int			i;
	char		dirs[5] = {'E', 'N', 'W', 'S', 0};

	i = 0;
	g->player.px = x;
	g->player.py = y;
	while (dirs[i])
	{
		if (c == dirs[i])
			break ;
		i++;
	}
	g->player.rad = i * (PI / 2);
	g->player.fov = 60;
}

int check_player(char **map, t_game *game)
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
			return (free(checkme), 1);
		if (!i || i == g->map_height)
			if (check_vert(checkme))
				return (free(checkme), 1);
		free(checkme);
		i++;
	}
	
	return (0);
}

int	check_surrounding(char **map, int x, int y, t_game *g)
{
	if ((x && !is_char(map[y][x - 1], " 1")) || 
		( x < g->map_width - 1 && !is_char(map[y][x + 1], " 1")) ||
		(y && !is_char(map[y - 1][x], " 1")) ||
		(y < g->map_height - 2 && !is_char(map[y + 1][x], " 1")) ||
		(y && x && !is_char(map[y - 1][x - 1], " 1"))||
		( y < g->map_height - 2 && x && !is_char(map[y + 1][x - 1], " 1"))||
		(y && x < g->map_width - 1&& !is_char(map[y - 1][x + 1], " 1"))||
		(x < g->map_width - 1 && y < g->map_height - 2 && !is_char(map[y + 1][x + 1], " 1")))
		return (printf("X:%d\nY:%d\n", x, y), 1);
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
	if (!map)
		return (write(2, "no map\n", 7));
    if (check_player(map, g))
	{
		printf("player\n");
		return (1);
	}
	if (check_walls(map, g))
	{
		printf("walls\n");
		return (1);
	}
	if (check_spaces(map, g))
	{
		printf("space\n");
		return (1);
	}
    // get_player_location(g);
	return (0);
}