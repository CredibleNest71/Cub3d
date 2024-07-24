/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:11:42 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/24 17:18:36 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	fin_read(t_tex *tex)
{
	if (!tex->c)
		return (0);
	if (!tex->f)
		return (0);
	if (!tex->no)
		return (0);
	if (!tex->we)
		return (0);
	if (!tex->ea)
		return (0);
	if (!tex->so)
		return (0);
	return (1);
}

char	**identify(t_tex *tex, char *line, int *color)
{
	*color = 0;
	if (!ft_strncmp(line, "NO ", 3) && !tex->no)
		return (&tex->no);
	if (!ft_strncmp(line, "SO ", 3) && !tex->so)
		return (&tex->so);
	if (!ft_strncmp(line, "EA ", 3) && !tex->ea)
		return (&tex->ea);
	if (!ft_strncmp(line, "WE ", 3) && !tex->we)
		return (&tex->we);
	if (!ft_strncmp(line, "F", 1) && !tex->f)
	{
		*color = 1;
		return (&tex->f);
	}
	if (!ft_strncmp(line, "C", 1) && !tex->c)
	{
		*color = 1;
		return (&tex->c);
	}
	write(2, "Error: couldnt identify!", 24);
	return (NULL);
}

int	add_to_textures(t_tex *tex, char *line)
{
	char	**curr;
	char	*found;
	char	*path;
	int		color;

	if (!line)
		return (0);
	curr = identify(tex, line, &color);
	if (!curr)
		return (free_and_null((void **)&line), 0);
	if (!color)
		found = ft_strchr(line, '.');
	else
		found = line;
	if (!found)
		return (free_and_null((void **)&line), 0);
	path = ft_strdup(found);
	if (path)
		path[ft_strlen(path) - 1] = 0;
	free_and_null((void **)&line);
	*curr = path;
	return (1);
}
