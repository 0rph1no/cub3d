/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:41:08 by ceddibao          #+#    #+#             */
/*   Updated: 2023/05/14 02:03:13 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	n_s(t_data *data)
{
	if (data->fin_9ass == 'y')
	{
		if (data->p_y > data->inter_x)
			return ('N');
		return ('S');
	}
	return (0);
}

char	e_w(t_data *data)
{
	if (data->fin_9ass == 'x')
	{
		if (data->p_x > data->inter_x)
			return ('W');
		return ('E');
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int color, int flag)
{
	char			*dst;
	unsigned int	toput;

	if (x < 0 || x >= data->screen_width || data->start_y < \
	0 || data->start_y >= data->screen_height)
		return ;
	dst = data->mlx_bgimage_addr + (data->start_y * \
	data->line_length + x * (data->bits_per_pixel / 8));
	if (data->fin_9ass == 'x')
		do_put_for_x(data, &toput);
	else
		do_put_for_y(data, &toput);
	if (flag == 0)
		*(unsigned int *)dst = toput;
	else if (flag == 1)
		*(unsigned int *)dst = color;
}

void	draw_rect(t_data *data)
{
	int		steps;
	double	cstart_y;
	double	end_y;
	double i = 0;

	data->middle_y = round(data->screen_height / 2);
	data->wall_height = round((64 / data->df) * 200);
	data->start_y = round(data->middle_y - (data->wall_height / 2));
	end_y = round(data->start_y + data->wall_height);
	cstart_y = data->start_y;
	steps = data->text_height / data->wall_height;
	data->wall_start = 0;
	while (i < end_y)
	{
		my_mlx_pixel_put(data, data->start_x, data->c_colour, 1);
		i++;
	}
	while (end_y > data->start_y)
	{
		my_mlx_pixel_put(data, data->start_x, 0xFFFFFF, 0);
		data->start_y++;
		data->wall_start++;
	}
	data->start_y = end_y;
	while (data->screen_height > data->start_y)
	{
		my_mlx_pixel_put(data, data->start_x, data->f_colour, 1);
		data->start_y++;
	}
	data->start_x++;
}
