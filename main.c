#include "includes/cub3d.h"
#include "includes/get_next_line.h"

double drawLine(t_data *data, double x1, double y1)
{
	double temp_x;
	double temp_y;
    while (1) {
		temp_x = x1;
		temp_y = y1;
		x1 += cos(turn_to_rad(data->fstrayy)) / 16;
		if (detect_colation(data->map, y1, x1, data->p_angle) == 0)
		{
			data->inter_y = y1;
			data->inter_x = x1;
			data->fin_9ass = 'x';
			return (sqrt(pow(x1 - data->p_x, 2) + pow(y1 - data->p_y, 2)));
		}
		y1 -= sin(turn_to_rad(data->fstrayy)) / 16;
		if (detect_colation(data->map, y1, x1, data->p_angle) == 0)
		{
			data->inter_y = x1;
			data->inter_x = y1;
			data->fin_9ass = 'y';
			return (sqrt(pow(x1 - data->p_x, 2) + pow(y1 - data->p_y, 2)));
		}
    }
	return -1;
}


void	draw_pixels(t_data *data)
{
	mlx_clear_window(data-> mlx_instance, data->mlx_window);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx_instance, data->mlx_window, data->mlx_bgimage, 0, 0);
}

int	key_hook(int keycode, t_all *all)
{
	t_data *data;
	data = &all->data;
	mlx_destroy_image(data->mlx_instance, data->mlx_bgimage);
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

	ft_parsing(&all, av[1]);
	ft_execution(&all);
	int i;
	i = 0;
	return ac;
}
