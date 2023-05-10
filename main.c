#include "includes/cub3d.h"
#include "includes/get_next_line.h"

void put_player_cube(t_data *data)
{
	mlx_pixel_put(data->mlx_instance, data->mlx_window, data->i, data->j, 0X800000);
}

double drawLine(t_data *data, double x1, double y1)
{
//	double ca;
	double temp_x;
	double temp_y;
    while (1) {
		temp_x = x1;
		temp_y = y1;
		//my_mlx_pixel_put(data, x1, y1, 0x80FFFF, 1, 0);
		x1 += cos(turn_to_rad(data->fstrayy)) / 16;
		if (detect_colation(data->map, y1, x1, data->p_angle) == 0)
		{
			//fprintf(stderr,"{%f}--{ %f}----{%c}\n", (x1 - 1)/64/minimap_scale, x1, data->map[(int)temp_y/64/minimap_scale][(int)x1/64/minimap_scale]);
			if (
				data->map[(int)y1/64/minimap_scale][(int)temp_x/64/minimap_scale] == '0'  
				)
				data->inter_y = x1;
			else
				data->inter_y = y1;
			data->fin_9ass = 'x';
			// printf("{w: %f\n}", data->inter_y);
			return (sqrt(pow(x1 - data->p_x, 2) + pow(y1 - data->p_y, 2)));
		}
		y1 -= sin(turn_to_rad(data->fstrayy)) / 16;
		if (detect_colation(data->map, y1, x1, data->p_angle) == 0)
		{
			//fprintf(stderr,"{%f}--{ %f}----{%c}\n", (x1 - 1)/64/minimap_scale, x1, data->map[(int)temp_y/64/minimap_scale][(int)x1/64/minimap_scale]);
			if (
				data->map[(int)temp_y/64/minimap_scale][(int)x1/64/minimap_scale] == '0'  
				)
				data->inter_y = y1;
			else
				data->inter_y = x1;
			data->fin_9ass = 'y';
			// printf("{s: %f\n}", data->inter_y);
			return (sqrt(pow(x1 - data->p_x, 2) + pow(y1 - data->p_y, 2)));
		}
    }
	return -1;
}


void	draw_pixels(t_data *data)
{
	// int i = 0;
	// int j = 0;
	// int x = 0;
	// int y = 0;
	// 	while(data->map[i])
	// 	{
	// 		while(data->map[i][j] && data->map[i][j] != '\n')
	// 		{
	// 			if (data->map[i][j] == '1')
	// 			{
	// 				x = 0;
	// 				y = 0;
	// 				while(y < 64 / minimap_scale)
	// 				{
	// 					while(x < 64 / minimap_scale)
	// 					{
	// 						my_mlx_pixel_put(data,(j * 64 / minimap_scale) + y ,  (i * 64 / minimap_scale) + x, 0xF629290, 1, 0);
	// 						x++;
	// 					}
	// 					y++;
	// 					x = 0;
	// 				}
	// 			}
	// 			else if (data->map[i][j] == '0')
	// 			{
	// 				x = 0;
	// 				y = 0;
	// 				while(y < 64 / minimap_scale)
	// 				{
	// 					while(x < 64 / minimap_scale)
	// 					{
	// 						my_mlx_pixel_put(data,(j * 64 / minimap_scale) + y ,  (i * 64 / minimap_scale) + x, 0xe3e3e3, 1, 0);
	// 						x++;
	// 					}
	// 					y++;
	// 					x = 0;
	// 				}
	// 			}
	// 			else if (data->map[i][j] == 'N')
	// 			{
	// 				x = 0;
	// 				y = 0;
	// 				while(y < 64 / minimap_scale)
	// 				{
	// 					while(x < 64 / minimap_scale)
	// 					{
	// 						my_mlx_pixel_put(data,(j * 64 / minimap_scale) + y ,  (i * 64 / minimap_scale) + x, 0xe3e3e3, 1, 0);
	// 						x++;
	// 					}
	// 					y++;
	// 					x = 0;
	// 				}
	// 			}
	// 			my_mlx_pixel_put(data,data->p_x,  data->p_y, 0x00FF00, 1, 0);
	// 			j++;
	// 		}
	// 		i++;
	// 		j = 0;
	// 	}


	cast_rays(data);
	mlx_put_image_to_window(data->mlx_instance, data->mlx_window, data->mlx_bgimage, 0, 0);
}

int	key_hook(int keycode, t_all *all)
{
	t_data *data;
	data = all->data;
	// printf("{%f}\n" , data->p_angle);
	data->mlx_bgimage = mlx_new_image(data->mlx_instance, data->screen_width, data->screen_height);
	data->mlx_bgimage_addr = mlx_get_data_addr(data->mlx_bgimage, &data->bits_per_pixel, &data->line_length, &data->endian);
	if (keycode == 123)
	{
		data->p_angle+=5;
		if (data->p_angle > 360)
			data->p_angle = data->p_angle - 360;
		draw_pixels(data);
	}
	else if (keycode == 124)
	{
		data->p_angle-=5;
		if (data->p_angle < 0)
			data->p_angle = 360 + data->p_angle;
		draw_pixels(data);
	}

	else if (keycode == 13)
	{
		double player_cos = (cos(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		double player_sin = (sin(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		data->p_x+=player_cos;
		data->p_y-=player_sin;
		if (detect_colation(data->map, data->p_y, data->p_x, data->p_angle) == 0)
		{
			data->p_x-=player_cos;
			data->p_y+=player_sin;
			return 0;
		}
		draw_pixels(data);
	}
	else if (keycode == 1)
	{
		double player_cos = (cos(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		double player_sin = (sin(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		data->p_x -= player_cos;
		data->p_y += player_sin;
		if (detect_colation(data->map, data->p_y, data->p_x, data->p_angle) == 0)
		{
			data->p_x+=player_cos;
			data->p_y-=player_sin;
			return 0;
		}
		draw_pixels(data);
	}
	else if (keycode == 0)
	{
		double player_cos = (cos(turn_to_rad(data->p_angle + 90)) * data->p_speed) / minimap_scale;
		double player_sin = (sin(turn_to_rad(data->p_angle + 90)) * data->p_speed) / minimap_scale;
		data->p_x+=player_cos;
		data->p_y-=player_sin;
		//printf("{%f----%f}\n", data->p_y, data->p_x);
		if (detect_colation(data->map, data->p_y, data->p_x, data->p_angle) == 0)
		{
			data->p_x-=player_cos;
			data->p_y+=player_sin;
			return 0;
		}
		draw_pixels(data);
	}
	else if (keycode == 2)
	{
		double player_cos = (cos(turn_to_rad(data->p_angle - 90)) * data->p_speed) / minimap_scale;
		double player_sin = (sin(turn_to_rad(data->p_angle - 90)) * data->p_speed) / minimap_scale;
		data->p_x+=player_cos;
		data->p_y-=player_sin;
		if (detect_colation(data->map, data->p_y, data->p_x, data->p_angle) == 0)
		{
			data->p_x-=player_cos;
			data->p_y+=player_sin;
			return 0;
		}
		draw_pixels(data);
	}
	return 0;
}

int main(int ac, char **av)
{
	t_all all;
	all.data = malloc(sizeof(sizeof(t_data)));

	ft_parsing(&all, av[1]);
	//printf("sdsdfsdfdsfdsf%s\n", all.map->use[0]);
	ft_execution(&all);
	int i;
	i = 0;
	return ac;
}
