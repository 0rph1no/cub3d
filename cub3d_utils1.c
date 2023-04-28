#include "includes/cub3d.h"
#include "includes/get_next_line.h"

int ft_strlen(char *s)
{
	int i = 0;
	while(s && s[i])
		i++;
	return i;
}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx_bgimage_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_rect(t_data *data)
{
    data->middle_y = data->screen_height / 2;
	double wall_height = (64 / data->df) * 120;
	if (wall_height > data->screen_height)
		wall_height = data->screen_height;
		//fprintf(stderr, "{%f---%f}\n", data->df, wall_height);
	double start_y =  data->middle_y - (wall_height / 2);
	double end_y = start_y + wall_height;
	while(end_y > start_y)
	{
		my_mlx_pixel_put(data, data->start_x, start_y, 0xFFFFFF);
		start_y++;
	}
	data->start_x++;
}

void DDA(t_data *data, int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(data, X, Y, 0xFFFFFF); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        //delay(100); // for visualization of line-
                    // generation step by step
    }
}

void draw_line_with_width(t_data *data, int x, int y1, int y2, int width, int color)
{
    // Calculate the half-width of the line
    int half_width = width / 2;
    
    // Draw multiple lines next to each other to simulate the desired width
    for (int i = 0; i <= half_width; i++) {
        my_mlx_pixel_put(data, x+i, y1, color);
        my_mlx_pixel_put(data, x+i, y2, color);
    }
	printf("fdsf\n");
}


void cast_rays(t_data *data)
{
	//double temp = 1920;
	data->start_x = 0;
	double fst_ray = data->p_angle + (data->fov / 2);
	double ray_end = fst_ray - data->fov;
	// //data->num_rays = 0;
	// //fprintf(stderr,"{%f----%f---%f}\n", fst_ray, ray_end, data->p_x);
	int newx;
	int newy;
	//int index_ray = 1;
	// fprintf(stderr, "{%f}", )
	while(fst_ray >= ray_end)
	{
		newx = data->p_x + ((data->screen_width) * cos(turn_to_rad(fst_ray)));
		newy = data->p_y - ((data->screen_height) * sin(turn_to_rad(fst_ray)));
		data->df = drawLine(data, data->p_x, data->p_y, newx, newy);
		draw_rect(data);
		// data->middle_x = data->screen_width / 2;
		//double wall_width = 1;
		//fprintf(stderr, "{%f---%f---%f---%f}\n", data->middle_y, start_y, data->screen_height, data->start_x);
		//double end_x = data->start_x + wall_width;
		//fprintf(stderr, "%f----%f---", start, end);
		//double temp = data->middle_x;
		// while(end_x > data->start_x)
		// {
		// }
		// start_x+=8;
		// while(start_x < data->middle_x + 100)
		// {
		// 	my_mlx_pixel_put(data, start_x, start_y, 0xFFFFFF);
		// 	start_x++;
		// }
		
		//fprintf(stderr, "player pos %f---%f----%f\n", data->p_x, data->p_y, data->df);
		// double wall_pos_x = data->df + data->p_x;
		// double wall_pos_y = data->df - data->p_y;
		// double wall_height = data->screen_height - data->df;
		
		// double wall_x = WALL_WIDTH;
		// data->wall_height = (data->screen_height) / data->df;
		// //fprintf(stderr,"wall heigh: %f---%f\n", data->wall_height, data->df);
		// if (data->wall_height > data->screen_height)
		// 	data->wall_height = data->screen_height;
		//  for (double y = 0; y < data->wall_height; y++) {
        // 	my_mlx_pixel_put(data, wall_x, y, 0xFFFFFF);
		// 	wall_x--;
   		//  }
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

void fill_map(char **map, t_data *data)
{
	int i = 0;

	map[i] = get_next_line(data->map_file);
	while(map[i++])
	{
		map[i] = get_next_line(data->map_file);
	}
}