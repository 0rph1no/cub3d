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
