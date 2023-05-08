#include "includes/cub3d.h"
#include "includes/get_next_line.h"

int ft_strlen(char *s)
{
	int i = 0;
	while(s && s[i])
		i++;
	return i;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color, int flag, int wstart)
{
	// int temp = wstart;
	char	*dst;
	int fill_x = 0;
	dst = data->mlx_bgimage_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (data->fin_9ass == 'x')
	{
		fill_x = data->inter_y * (float)data->text_width / 16;
		if (fill_x > data->text_width)
			fill_x %= data->text_width;
	}
	else
		flag = 1; // calculate the corresponding x-coordinate in the fill image
	// fprintf(stderr, "{%d-----}\n", data->text_width);
    int fill_y =  (int)((wstart) * data->text_height / data->wall_height) % data->text_height;
	int fill_offset = fill_y * data->text_line_length + fill_x * (data->bpp / 8);
	unsigned int toput = *(unsigned int *)(data->text_image_addr + fill_offset);
	if (flag == 0)
		*(unsigned int*)dst = toput;
	else
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
	double end_y = round(start_y + data->wall_height);//749
	cstart_y = start_y;
	fstart_y =  end_y;
	steps = data->text_height / data->wall_height;
	//fprintf(stderr, "{%d---%f---%d}\n", steps, wall_height, data->text_height);
	while(end_y > start_y)
	{
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
	//fprintf(stderr, "{%f----%f}\n", fst_ray, ray_end);
	// int newx;
	// int newy;
	//int c = 0;
	while(fst_ray > ray_end)
	{
		data->fstrayy = fst_ray;
		// newx = data->p_x + ((data->screen_width) * cos(turn_to_rad(fst_ray)));
		// newy = data->p_y - ( (data->screen_height) * sin(turn_to_rad(fst_ray)));
		data->df = drawLine(data, data->p_x, data->p_y);
		//c++;
		data->df = data->df * cos(turn_to_rad(fst_ray - data->p_angle));
		draw_rect(data);
		fst_ray = fst_ray - (64 / data->screen_width);
	}
	//fprintf(stderr, "{%d}\n", c);
}

// void cast_rays(t_data *data)
// {
// 	data->start_x = 0;
// 	double fst_ray = data->p_angle + (data->fov / 2);
// 	double ray_end = fst_ray - data->fov;
// 	double newx;
// 	double newy;
// 	double nin_dif_x;
// 	double nin_dif_y;
// 	double diff;
// 	double end_dif_x;
// 	double end_dif_y;
// 	double end_diff;
// 	//double temp;
// 	nin_dif_x = data->p_x + ((data->screen_width) * cos(turn_to_rad(data->p_angle)));
// 	nin_dif_y = data->p_y - ( (data->screen_height) * sin(turn_to_rad(data->p_angle)));
// 	diff = drawLine(data, data->p_x, data->p_y, nin_dif_x, nin_dif_y);
// 	end_dif_x = data->p_x + ((data->screen_width) * cos(turn_to_rad(ray_end)));
// 	end_dif_y = data->p_y - ( (data->screen_height) * sin(turn_to_rad(ray_end)));
// 	end_diff = drawLine(data, data->p_x, data->p_y, end_dif_x, end_dif_y);
// 	while(fst_ray >= ray_end)
// 	{
// 		data->fstrayy = fst_ray;
// 		newx = data->p_x + ((data->screen_width) * cos(turn_to_rad(fst_ray)));
// 		newy = data->p_y - ( (data->screen_height) * sin(turn_to_rad(fst_ray)));
// 		data->df = drawLine(data, data->p_x, data->p_y, newx, newy);
// 		data->df =  end_diff * cos(diff / end_diff);
// 		draw_rect(data);
// 		fst_ray = fst_ray - (64 / data->screen_width);
// 	}	
// }



int get_map_height(char **map)
{
	int i = 0;
	while(map[i])
		i++;
	return i;
}

void fill_map(char **map, t_data *data)
{
	int i = 0;

	map[i] = get_next_line(data->map_file);
	while(map[i++])
	{
		map[i] = get_next_line(data->map_file);
	}
}