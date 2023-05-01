/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:20:28 by abouzanb          #+#    #+#             */
/*   Updated: 2023/05/01 00:49:28 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <strings.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_S
{
	int x;
	int space;
	int i;
	int a;
	int player;
	int wall;
}t_l;
typedef struct s_ray
{
	double length;
	double player_pos;
	double *rays;
}t_ray;

typedef struct s_map
{
	char	**map;
	char	**temp;
	char	**use;
	char	*name;
	int		big_size;
	int		row_number;
}t_map;

typedef struct s_emelemnts
{
	char *ea;
	char *so;
	char *we;
	char *no;
	char *f_temp;
	char *c_temp;
}t_elem;

typedef struct s_text_colo
{
	void *ea;
	void *so;
	void *we;
	void *no;
	int f;
	int c;
}t_struct;



typedef struct s_data
{
	double fstrayy;
	void *mlx_instance;
	void *mlx_window;
	void *mlx_bgimage;
	char *mlx_bgimage_addr;
	double fov;
	double plane_dim_x;
	double plane_dim_y;
	double plane_center_dim;
	double dtp; //distance to plane
	double dbr; //distance between rays
	int	i;
	int	j;
	double	p_x;
	double	p_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int pcube_center_x;
	int pcube_center_y;
	int	map_width;
	int map_height;
	int	map_file;
	double screen_width;
	double screen_height;
	char **map;
	double p_angle;
	double p_speed;
	double p_rot_speed;
	double turnDir;
	double walkDir;
	int *map_walls;
	int flag;
	double df;
	double num_rays;
	double color;
	double wall_height;
	double middle_x;
	double middle_y;
	double start_x;
	t_ray *ray;
	
}t_data;

typedef struct s_all
{
	t_data *data;
	
	t_struct *tool;
	t_map *map;
	t_elem *elem;
}t_all;
#define mapWidth 20
#define mapHeight 20
#define screenWidth 600
#define screenHeight 080
#define PI 3.10
#define minimap_scale 4
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define WALL_HEIGHT 50
#define WALL_WIDTH 8


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_map_height(char **map);
int		ft_strlen(char *s);
void	fill_map(char **map, t_data *data);
int		get_player_pos(char **map, int flag);
int		detect_colation(char **map, int x, int y, double angle);
void	do_dda(t_data *data, int x1, int y1, int x2, int y2);
double	turn_to_rad(double deg);
double	drawLine(t_data *data, double x1, double y1, double x2, double y2);
void	cast_rays(t_data *data);
void draw_3d_wall(t_data *data, int ray_index, double distance);
void draw_walls(t_data *data, char **map);
void project_wall(t_data *data, int x1, int y1,int x2, int y2);
void project_wall(t_data *data, int x1, int y1,int x2, int y2);
char	*ft_strtrim(char *s1, char  *set);
char	*ft_substr(char  *str, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*my_strtrim(char *s1, char  *set);
void cast(t_data *data);