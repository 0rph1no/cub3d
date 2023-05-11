#include "includes/cub3d.h"
#include "includes/get_next_line.h"

int ft_strlen(char *s)
{
	int i = 0;
	while(s && s[i])
		i++;
	return i;
}

char n_s(t_data *data)
{
	if (data->fin_9ass == 'y')
	{
		if (data->p_y > data->inter_x)
			return ('N');
		return ('S');
	}
	return 0;
}
char e_w(t_data *data)
{
	if (data->fin_9ass =='x')
	{
		if (data->p_x > data->inter_x)
			return ('W');
		return ('E');
	}
	return 0;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color, int flag, int wstart)
{
	char	*dst;
	int fill_y;
	int fill_offset;
	unsigned int toput;
	int fill_x = 0;
	dst = data->mlx_bgimage_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (data->fin_9ass == 'x')
	{
		if (e_w(data) == 'E')
		{
				fill_x = data->inter_y * (float)data->ea.text_width/ 16;
				if (fill_x > data->ea.text_width)
					fill_x %= data->ea.text_width;
				fill_y =  (int)((wstart) * data->ea.text_height / data->wall_height) % data->ea.text_height;
				fill_offset = fill_y * data->ea.text_line_lenght + fill_x * (data->ea.bit_per_pixel / 8);
				toput = *(unsigned int *)(data->ea.text + fill_offset);
		}
		else
		{
				fill_x = data->inter_y * (float)data->we.text_width/ 16;
				if (fill_x > data->we.text_width)
					fill_x %= data->we.text_width;
				fill_y =  (int)((wstart) * data->we.text_height / data->wall_height) % data->we.text_height;
				fill_offset = fill_y * data->we.text_line_lenght + fill_x * (data->we.bit_per_pixel / 8);
				toput = *(unsigned int *)(data->we.text + fill_offset);
		}
	}
	else
	{
			if (n_s(data) == 'S')
			{
				fill_x = data->inter_y * (float)data->so.text_width/ 16;
				if (fill_x > data->so.text_width)
					fill_x %= data->so.text_width;
				fill_y =  (int)((wstart) * data->so.text_height / data->wall_height) % data->so.text_height;
				fill_offset = fill_y * data->so.text_line_lenght + fill_x * (data->so.bit_per_pixel / 8);
				toput = *(unsigned int *)(data->so.text + fill_offset);
			}
			else
			{
				fill_x = data->inter_y * (float)data->no.text_width/ 16;
				if (fill_x > data->no.text_width)
					fill_x %= data->no.text_width;
				fill_y =  (int)((wstart) * data->no.text_height / data->wall_height) % data->no.text_height;
				fill_offset = fill_y * data->no.text_line_lenght + fill_x * (data->no.bit_per_pixel / 8);
				toput = *(unsigned int *)(data->no.text + fill_offset);
			}
	}
	if (flag == 0)
		*(unsigned int*)dst = toput;
	else if (flag == 1)
		*(unsigned int*)dst = color;
		
}

void draw_rect(t_data *data)
{
	int steps;
	double fstart_y;
	double cstart_y;
	int wall_start = 0;
    data->middle_y = round(data->screen_height / 2);
	data->wall_height = round((64 / data->df) * 200);
	if (data->wall_height > data->screen_height)
		data->wall_height = data->screen_height;
	double start_y =  round(data->middle_y - (data->wall_height / 2));
	double end_y = round(start_y + data->wall_height);
	cstart_y = start_y;
	fstart_y =  end_y;
	steps = data->text_height / data->wall_height;
	while(end_y > start_y)
	{
		if (n_s(data) == 'S')
			my_mlx_pixel_put(data, data->start_x, start_y, 0x008000, 0, wall_start);
		else
			my_mlx_pixel_put(data, data->start_x, start_y, 0xFFFFFF, 0, wall_start);
		start_y++;
		wall_start++;
	}
	while(data->screen_height > fstart_y)
	{
		my_mlx_pixel_put(data, data->start_x, fstart_y, 0xD84242, 1, wall_start);
		fstart_y++;
	}
	data->start_x++;
}

void cast_rays(t_data *data)
{
	data->start_x = 0;
	double fst_ray = data->p_angle + (data->fov / 2);
	double ray_end = fst_ray - data->fov;
	while(fst_ray > ray_end)
	{
		data->fstrayy = fst_ray;
		data->lstrayy = ray_end;
		data->df = drawLine(data, data->p_x, data->p_y);
		data->df = data->df * cos(turn_to_rad(fst_ray - data->p_angle));
		draw_rect(data);
		fst_ray = fst_ray - (60 / data->screen_width);
	}
}

int get_map_height(char **map)
{
	int i = 0;
	while(map[i])
		i++;
	return i;
}
