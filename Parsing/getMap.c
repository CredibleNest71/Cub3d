/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:47:26 by mresch            #+#    #+#             */
/*   Updated: 2024/07/17 15:17:45 by mesenyur         ###   ########.fr       */
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
	free_and_null((void **)&first);
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
		line = append_and_replace(line, next); // free line
		// printf("mem: %p\n", line);
		next = get_next_line(fd);
		if (next && ft_strlen(next) < 2)
		{
			if (next)
				free_and_null((void **)&next);
			return NULL ;
		}
	}
	if (next)
		free_and_null((void **)&next);
	// printf("READMAP: %s", line);
	return (line);
}

void		set_proportions(char *line, int	*height, int *width)
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
			if (w - 1> *width)
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
			return (NULL);
		while (line[j] && line[j] != '\n' && k < width)
			map[i][k++] = line[j++];
		while (k < width)
			map[i][k++] = ' ';
		j++;
		i++;
	}
	// printf("\nMAKEMAPARRAY:");
	// print_map(map);
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
	// if (!width || !height)
	// 	return (perror("Error::make_array\n"), NULL);
	g->map_height = height;
	g->map_width = width;
	map = make_array(line, height, width);
	return (map);
}
char	**getMap(int fd, t_game *g)
{
	char	*temp;
	char	*oneline;
	char	**map;
	// (void)fd;
	oneline = read_map(fd); // if null gnl leaks 1 byte
	if (!oneline)
		return (NULL);
	if (oneline[ft_strlen(oneline) - 1] != '\n')
	{
		temp = ft_strjoin(oneline, "\n");
		free_and_null((void **)&oneline);
		oneline = temp;
	}
	map = make_map(oneline, g);
	free_and_null((void **)&oneline);
	return (map);
}

// void	print_map(char **map)
// {
// 	printf("\n==========================\n");
//     for (int i = 0; map[i]; i++)
//     {
// 	    printf("|%s|\n", map[i]);
// 	}
// 	printf("==========================\n");
// }
