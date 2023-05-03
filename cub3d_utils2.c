#include "includes/cub3d.h"

int get_player_pos(char **map, int flag)
{
	int i = 0;
	int j = 0;
	while(map[i])
	{
		while(map[i][j])
		{
			if (map[i][j] == 'N')
			{
				if (flag == 0)
					return j;
				return i;
			}
			j++;
		}
		i++;
		j = 0;
	}
	return -1;
}

int detect_colation(char **map, int py, int px, double angle)
{
	(void)angle;
	int newx;
	int newy;
	int i = 0;

	newx = px / (64 / minimap_scale);
	newy = py / (64 / minimap_scale);
	// if (newy > 0)
	// 	i  = ft_strlen(map[newy]);
	// if (i == 0)
	// 	return (0);
 	 if (map[newy][newx] && ( map[newy][newx] == '1'))
		return 0;
	return 1;
}

double turn_to_rad(double deg)
{
	return (deg * (PI / 180.0));
}

int do_all(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data *data;
	data = (t_data*)malloc(sizeof(t_data));
	data->map_file = open(av[1], O_RDONLY, 0677);
	if (data->map_file == -1)
	{
		free(data);
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
	data->p_speed = 20;
	data->p_rot_speed = 15;
	data->i = 400;
	data->color = 50;
	data->screen_width = 1920;
	data->screen_height = 1080;
	data->dtp = data->plane_center_dim / tan(turn_to_rad(30));
	assert(data->mlx_instance != NULL);
	data->mlx_window = mlx_new_window(data->mlx_instance, data->screen_width, data->screen_height, "charaf windows");
	assert(data->mlx_window != NULL);
	data->mlx_bgimage = mlx_new_image(data->mlx_instance, data->screen_width, data->screen_height);
	assert(data->mlx_bgimage != NULL);
	data->mlx_bgimage_addr = mlx_get_data_addr(data->mlx_bgimage, &data->bits_per_pixel, &data->line_length, &data->endian);
	assert(data->mlx_bgimage != NULL);
	data->j = 50;
	draw_pixels(data);
	mlx_put_image_to_window(data->mlx_instance, data->mlx_window, data->mlx_bgimage, 0, 0);
	mlx_hook(data->mlx_window, 2, 1L << 0, key_hook, data);
	mlx_loop(data->mlx_instance);
	return 0;
}
