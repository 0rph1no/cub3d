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

int ft_execution(t_all *all)
{
	all->data->map_width = ft_strlen(all->data->map[0]);
	//fprintf(stderr, "sdfdsfsfsf\n");
	all->data->map_height = get_map_height(all->data->map);
	all->data->p_x = get_player_pos(all->data->map, 0) * (66 / minimap_scale);
	all->data->p_y = get_player_pos(all->data->map, 1) * (66 / minimap_scale);
	all->data->mlx_instance = mlx_init();
	all->data->fov = 60;
	all->data->plane_dim_x = 320;
	all->data->plane_dim_y = 120;
	all->data->p_angle = 90;
	all->data->p_speed = 20;
	all->data->p_rot_speed = 15;
	all->data->i = 400;
	all->data->color = 50;
	all->data->screen_width = 1200;
	all->data->screen_height = 1000;
	all->data->dtp = all->data->plane_center_dim / tan(turn_to_rad(30));
	all->data->mlx_window = mlx_new_window(all->data->mlx_instance, all->data->screen_width, all->data->screen_height, "charaf windows");
	all->data->mlx_bgimage = mlx_new_image(all->data->mlx_instance, all->data->screen_width, all->data->screen_height);
	all->data->mlx_bgimage_addr = mlx_get_data_addr(all->data->mlx_bgimage, &all->data->bits_per_pixel, &all->data->line_length, &all->data->endian); 
	all->data->text_image = mlx_xpm_file_to_image(all->data->mlx_instance, "textures/text_no.xpm", &all->data->text_width, &all->data->text_height);
	all->data->text_image_addr = mlx_get_data_addr(all->data->text_image, &all->data->bpp, &all->data->text_line_length, &all->data->text_endian);
	all->data->j = 50;
	draw_pixels(all->data);
	mlx_put_image_to_window(all->data->mlx_instance, all->data->mlx_window, all->data->mlx_bgimage, 0, 0);
	mlx_hook(all->data->mlx_window, 2, 1L << 0, key_hook, all);
	mlx_loop(all->data->mlx_instance);
	return 0;
}

	//fprintf(stderr, "{%p}----{%p}---{%d}---{%d}\n ", data->mlx_bgimage_addr, data->mlx_bgimage_addr + 7680,data->line_length, data->bits_per_pixel);
	/*
		data.bpp => num of bits needed to draw a pixel with color // 32bit== 4byte
		data.linelength => num of bytes needed to store one line of the image in memory which will equal the screen width * data.bpp/8
	*/