/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:47:26 by mresch            #+#    #+#             */
/*   Updated: 2024/07/31 11:35:34 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <time.h>

char	*append_and_replace(char *first, char *second)
{
	char	*ret;

	if (!second)
		return (first);
	if (!first)
		return (second);
	ret = ft_strjoin(first, second);
	if (first)
		free_and_null((void **)&first);
	if (second)
		free_and_null((void **)&second);
	return (ret);
}

char	*read_map(int fd)
{
	char	*line;
	char	*next;

	line = NULL;
	next = get_next_line(fd);
	while (next && next[0] == '\n')
	{
		free_and_null((void **)&next);
		next = get_next_line(fd);
	}
	while (next)
	{
		line = append_and_replace(line, next);
		if (!line)
			return (NULL);
		next = get_next_line(fd);
		if (next && ft_strlen(next) < 2 && next[0] == '\n')
		{
			free_and_null((void **)&next);
			return ((free_and_null((void **)&line)), NULL);
		}
	}
	if (next)
		free_and_null((void **)&next);
	return (line);
}

void	set_proportions(char *line, int	*height, int *width)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (line[i])
	{
		w++;
		if (line[i] == '\n')
		{
			if (w - 1 > *width)
				*width = w - 1;
			*height += 1;
			w = 0;
		}
		i++;
	}
	return ;
}

char	**make_array(char *line, int height, int width)
{
	char	**map;
	int		i;
	int		j;
	int		k;

	j = 0;
	i = 0;
	map = ft_calloc(height + 1, sizeof(char *));
	if (!map)
		return (NULL);
	while (i < height)
	{
		k = 0;
		map[i] = (char *) ft_calloc(1, width + 1);
		if (!map[i])
			return (free_words(map), NULL);
		while (line[j] && line[j] != '\n' && k < width)
			map[i][k++] = line[j++];
		while (k < width)
			map[i][k++] = ' ';
		j++;
		i++;
	}
	return (map);
}

char	**make_map(char *line, t_game *g)
{
	int		width;
	int		height;
	char	**map;

	width = 0;
	height = 0;
	set_proportions(line, &height, &width);
	g->map_height = height;
	g->map_width = width;
	map = make_array(line, height, width);
	if (!map)
	{
		free_and_null((void **)&line);
		return (ft_error(g, "Couldn't allocate memory for map", true), NULL);
	}
	return (map);
}
