/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:56 by mresch            #+#    #+#             */
/*   Updated: 2024/07/17 16:11:20 by mesenyur         ###   ########.fr       */
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

static char	**identify(t_tex *tex, char *line, int *color)
{
	*color = 0;
	if (!ft_strncmp(line, "NO", 2) && !tex->no)
		return (&tex->no);
	if (!ft_strncmp(line, "SO", 2) && !tex->so)
		return (&tex->so);
	if (!ft_strncmp(line, "EA", 2) && !tex->ea)
		return (&tex->ea);
	if (!ft_strncmp(line, "WE", 2) && !tex->we)
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

static int	add_to_textures(t_tex *tex, char *line)
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
	free_and_null((void **)&line);
	*curr = path;
	return (1);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	string_to_rgb(char *str)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (ft_isalpha(str[i]) || str[i] == ' ')
		i++;
	rgb[0] = ft_atoi(&str[i]);
	i = ft_strchr(&str[i], ',') - str + 1;
	rgb[1] = ft_atoi(&str[i]);
	i = ft_strchr(&str[i], ',') - str + 1;
	rgb[2] = ft_atoi(&str[i]);
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}

void	convert(t_game *g, t_tex *tex)
{
	int	h;
	int	w;

	tex->no_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->no, &h, &w);
	tex->so_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->so, &h, &w);
	tex->ea_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->ea, &h, &w);
	tex->we_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->we, &h, &w);
}

int	get_textures(int fd, t_tex *tex, t_game *g)
{
	char	*line;

	while (!fin_read(tex))
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (line[0] == '\n')
		{
			free_and_null((void **)&line);
			continue ;
		}
		if (!add_to_textures(tex, line))
			return (write(2, "An Error occurred\n", 18));
	}
	g->tex.c_rgb = string_to_rgb(tex->c);
	g->tex.f_rgb = string_to_rgb(tex->f);
	convert(g, tex);
	return (0);
}

void	delete_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i++]);
	}
	free(map);
}

void	delete_tex(t_tex *tex)
{
	if (tex->c)
		free(tex->c);
	if (tex->f)
		free(tex->f);
	if (tex->no)
		free(tex->no);
	if (tex->so)
		free(tex->so);
	if (tex->ea)
		free(tex->ea);
	if (tex->we)
		free(tex->we);
}
