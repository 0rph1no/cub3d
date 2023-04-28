#include "includes/cub3d.h"
#include "includes/get_next_line.h"

void put_player_cube(t_data *data)
{
	mlx_pixel_put(data->mlx_instance, data->mlx_window, data->i, data->j, 0X800000);
}

double drawLine(t_data *data, double x1, double y1, double x2, double y2)
{
    double dx = fabs(x2 - x1);
    double dy = fabs(y2 - y1);
    double sx = (x1 < x2) ? 1 : -1;
    double sy = (y1 < y2) ? 1 : -1;
    double err = dx - dy;
	double temp_x = x1;
	double temp_y = y1;
 
    while (1) {
		if (detect_colation(data->map, y1, x1, data->p_angle) == 0)
		{
			// if ((data->p_angle >= 0 && data->p_angle <= 45) || (data->p_angle >= 135 && data->p_angle<=225))
			// 	return fabs(x1 - data->p_x);
			// else if ((data->p_angle > 45 && data->p_angle <= 135) || (data->p_angle >225 && data->p_angle <= 315))
			// 	return fabs(y1 - data->p_y);
			// else if ((data->p_angle > 315 && data->p_angle <= 360))
			// 	return fabs(x1 - data->p_x);
			return sqrt(pow(x1 - temp_x, 2) + pow(y1 - temp_y, 2));
		}
		my_mlx_pixel_put(data,x1, y1, 0x800000);
        double e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
	return -1;
}

void	draw_pixels(t_data *data)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
		while(data->map[i])
		{
			while(data->map[i][j] && data->map[i][j] != '\n')
			{
				if (data->map[i][j] == '1')
				{
					x = 0;
					y = 0;
					while(y < 64 / minimap_scale)
					{
						while(x < 64 / minimap_scale)
						{
							my_mlx_pixel_put(data,(j * 64 / minimap_scale) + y ,  (i * 64 / minimap_scale) + x, 0xF629290);
							x++;
						}
						y++;
						x = 0;
					}
				}
				else if (data->map[i][j] == '0')
				{
					x = 0;
					y = 0;
					while(y < 64 / minimap_scale)
					{
						while(x < 64 / minimap_scale)
						{
							my_mlx_pixel_put(data,(j * 64 / minimap_scale) + y ,  (i * 64 / minimap_scale) + x, 0xe3e3e3);
							x++;
						}
						y++;
						x = 0;
					}
				}
				else if (data->map[i][j] == 'N')
				{
					x = 0;
					y = 0;
					while(y < 64 / minimap_scale)
					{
						while(x < 64 / minimap_scale)
						{
							my_mlx_pixel_put(data,(j * 64 / minimap_scale) + y ,  (i * 64 / minimap_scale) + x, 0xe3e3e3);
							x++;
						}
						y++;
						x = 0;
					}
				}
				my_mlx_pixel_put(data,data->p_x,  data->p_y, 0x00FF00);
				j++;
			}
			i++;
			j = 0;
		}
	cast_rays(data);
	mlx_put_image_to_window(data->mlx_instance, data->mlx_window, data->mlx_bgimage, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
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
		// if (data->flag == 1)
		// 	return 0;
		// data->j-=10;
		// data->color+=50;
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
		//mlx_clear_window(data->mlx_instance, data->mlx_window);
		draw_pixels(data);
	}
	else if (keycode == 1)
	{


		// if (data->p_y+10 > (data->map_height - 1)*64)
		// 	return 0;
		// if (detect_colation(data->map, ((data->p_y+10) / 64), ((data->p_x) / 64)) == 0)
		// 	return 0;
		// data->p_y +=10;
		double player_cos = (cos(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		double player_sin = (sin(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		data->p_x -= player_cos;
		data->p_y += player_sin;
		//fprintf(stderr, "{%f------%f}", data->p_x, data->p_y);
		if (detect_colation(data->map, data->p_y, data->p_x, data->p_angle) == 0)
		{
			//fprintf(stderr, "dsfsdfsd\n");
			data->p_x+=player_cos;
			data->p_y-=player_sin;
			return 0;
		}
		//mlx_clear_window(data->mlx_instance, data->mlx_window);
		draw_pixels(data);
	}
	else if (keycode == 0)
	{
		// if (data->p_x-10 <= 0)
		// 	return 0;
		// if (detect_colation(data->map, ((data->p_y) / 64), ((data->p_x-10) / 64)) == 0)
		// 	return 0;
		// data->p_x-=10;
		double player_cos = (cos(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		data->i = 0;
		data->j = 0;
		data->p_x -= player_cos;
		if (detect_colation(data->map, data->p_y, data->p_x, data->p_angle) == 0)
		{
			data->p_x+=player_cos;
			return 0;
		}
		draw_pixels(data);
	}
	else if (keycode == 2)
	{
		// if (data->p_x+10 >= (data->map_width - 1)*64)
		// 	return 0;
		// if (detect_colation(data->map, ((data->p_y) / 64), ((data->p_x+10) / 64)) == 0)
		// 	return 0;
		//data->p_x+=10;
		double player_cos = (cos(turn_to_rad(data->p_angle)) * data->p_speed) / minimap_scale;
		data->i = 0;
		data->j = 0;
		data->p_x += player_cos;
		if (detect_colation(data->map, data->p_y, data->p_x, data->p_angle) == 0)
		{
			data->p_x-=player_cos;
			return 0;
		}
		draw_pixels(data);
	}
	return 0;
}

int main(int ac, char **av)
{

	(void)ac;
	(void)av;
	t_data *data;
	t_ray *ray;
	data = (t_data*)malloc(sizeof(t_data));
	ray = (t_ray *)malloc(sizeof(t_ray) * 61);
	data->map_file = open(av[1], O_RDONLY, 0677);
	if (data->map_file == -1)
	{
		free(data);
		free(ray);
		return (1);
	}
	data->map = malloc(sizeof(char *) * 10);
	fill_map(data->map, data);
	data->map_width = ft_strlen(data->map[0]);
	data->map_height = get_map_height(data->map);
	data->p_x = get_player_pos(data->map, 0) * (66 / minimap_scale);
	data->p_y = get_player_pos(data->map, 1) * (66 / minimap_scale);
	data->mlx_instance = mlx_init();
	data->fov = 60;
	data->plane_dim_x = 320;
	data->plane_dim_y = 120;
	data->p_angle = 90;
	data->p_speed = 15;
	data->p_rot_speed = 15;
	data->ray = ray;
	// data->turnDir = 0;
	// data->walkDir = 0;
	// data->plane_center_dim = data->plane_dim_x / 2;
	data->i = 400;
	data->color = 50;
	data->screen_width = 1920;//(data->map_width - 1) * 64;
	data->screen_height = 1080;//(data->map_height) * 64;
	data->dtp = data->plane_center_dim / tan(turn_to_rad(30));
	assert(data->mlx_instance != NULL);
	data->mlx_window = mlx_new_window(data->mlx_instance, data->screen_width, data->screen_height, "charaf windows");
	assert(data->mlx_window != NULL);
	data->mlx_bgimage = mlx_new_image(data->mlx_instance, data->screen_width, data->screen_height);
	assert(data->mlx_bgimage != NULL);
	data->mlx_bgimage_addr = mlx_get_data_addr(data->mlx_bgimage, &data->bits_per_pixel, &data->line_length, &data->endian);
	assert(data->mlx_bgimage != NULL);
	//data->i = 0;
	data->j = 50;
	//draw_walls(data, data->map);
	draw_pixels(data);
	mlx_put_image_to_window(data->mlx_instance, data->mlx_window, data->mlx_bgimage, 0, 0);
	mlx_hook(data->mlx_window, 2, 1L << 0, key_hook, data);
	//mlx_key_hook(data->mlx_window, key_hook, data);
	mlx_loop(data->mlx_instance);
}