/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:56 by mresch            #+#    #+#             */
/*   Updated: 2024/07/24 17:17:17 by mresch           ###   ########.fr       */
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
	if (!ft_strncmp(line, "NO ", 3) && !tex->no)
		return (&tex->no);
	if (!ft_strncmp(line, "SO ", 3) && !tex->so)
		return (&tex->so);
	if (!ft_strncmp(line, "EA ", 3) && !tex->ea)
		return (&tex->ea);
	if (!ft_strncmp(line, "WE ", 3) && !tex->we)
		return (&tex->we);
	if (!ft_strncmp(line, "F ", 2) && !tex->f)
	{
		*color = 1;
		return (&tex->f);
	}
	if (!ft_strncmp(line, "C ", 2) && !tex->c)
	{
		*color = 1;
		return (&tex->c);
	}
	//write(2, "Error: couldnt identify!", 24);
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
	if (path)
		path[ft_strlen(path) - 1] = 0;
	free_and_null((void **)&line);
	*curr = path;
	return (1);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	check_rgb_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isdigit(str[i])))
		i++;
	if (str[i++] != ',')
		return (1);
	while (str[i] && (ft_isdigit(str[i])))
		i++;
	if (str[i++] != ',')
		return (1);
	while (str[i] && (ft_isdigit(str[i])))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
		i++;
	if (str[i])
		return (1);
	return (0);
}


int	string_to_rgb(char *str)
{
	int		j;
	int		i;
	int		rgb[3];
	char	*curr;

	i = 0;
	j = 0;
	if (check_rgb_str(str))
		return (-1);
	while (ft_isalpha(str[i]) || str[i] == ' ')
		i++;
	while (j < 2)
	{
		rgb[j] = ft_atoi(&str[i]);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (-1);
		curr = ft_strchr(&str[i], ',');
		if (!curr || !ft_isdigit(curr[1]))
			return (-1);
		i = curr - str + 1;
		j++;
	}
	rgb[2] = ft_atoi(&str[i]);
	if (rgb[2] < 0 || rgb[2] > 255)
		return (-1);
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}

int	convert(t_game *g, t_tex *tex)
{
	tex->no_info.image = mlx_xpm_file_to_image(g->minilibx.mlx, tex->no, &tex->no_info.w, &tex->no_info.h);
	tex->so_info.image = mlx_xpm_file_to_image(g->minilibx.mlx, tex->so, &tex->so_info.w, &tex->so_info.h);
	tex->ea_info.image = mlx_xpm_file_to_image(g->minilibx.mlx, tex->ea, &tex->ea_info.w, &tex->ea_info.h);
	tex->we_info.image = mlx_xpm_file_to_image(g->minilibx.mlx, tex->we, &tex->we_info.w, &tex->we_info.h);
	if (!tex->no_info.image || !tex->so_info.image || !tex->ea_info.image || !tex->we_info.image)
		return (ft_error(g, "Texture conversion failed"));
	tex->no_info.buf = mlx_get_data_addr(tex->no_info.image, &tex->no_info.bits_per_pixel,
			&tex->no_info.line_bytes, &tex->no_info.endian);
	tex->so_info.buf = mlx_get_data_addr(tex->so_info.image, &tex->so_info.bits_per_pixel,
			&tex->so_info.line_bytes, &tex->so_info.endian);
	tex->we_info.buf = mlx_get_data_addr(tex->we_info.image, &tex->we_info.bits_per_pixel,
			&tex->we_info.line_bytes, &tex->we_info.endian);
	tex->ea_info.buf = mlx_get_data_addr(tex->ea_info.image, &tex->ea_info.bits_per_pixel,
			&tex->ea_info.line_bytes, &tex->ea_info.endian);
	return (0);
}

int	get_textures(int fd, t_tex *tex, t_game *g)
{
	char	*line;

	if (fd == -1)
		return (-1);
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
			return (1);
	}
	g->tex.c_rgb = string_to_rgb(tex->c);
	g->tex.f_rgb = string_to_rgb(tex->f);
	if (convert(g, tex))
		return (ft_error(g, "Texture conversion failed"));
	if (g->tex.c_rgb == -1 || g->tex.f_rgb == -1)
		return (ft_error(g, "Texture conversion failed"));
	return (0);
}
