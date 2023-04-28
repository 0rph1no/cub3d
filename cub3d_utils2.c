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
	//printf("{%d, %d}\n", newx, newy);
	//fprintf(stderr, "{%d-----%d}\n", newx, newy);
	if (map[newy][newx] &&( map[newy][newx] == '1'))
		return 0;
	return 1;
}

void do_dda(t_data *data, int x1, int y1, int x2, int y2)
{
	//dda algo to draw a line 
	int dx = x2 - x1;
    int dy = y2 - y1;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = x1;
    float Y = y1;
    for (int i = 0; i <= steps; i++) {
       my_mlx_pixel_put(data, X, Y, 0x008000);
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        sleep(1); // for visualization of line-   // generation step by step
    }
}

double turn_to_rad(double deg)
{
	return (deg * (PI / 180.0));
}
