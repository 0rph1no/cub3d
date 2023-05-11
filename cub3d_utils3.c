/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 20:57:59 by abouzanb          #+#    #+#             */
/*   Updated: 2023/05/11 18:28:43 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/cub3d.h"



size_t	ft_strlcpy(char *dest, char *str, size_t size)
{
	size_t	x;
	size_t	size_compare;

	x = 0;
	size_compare = 0;
	if (size == 0)
		return (ft_strlen(str));
	while (str[x] != '\0' && size_compare < (size))
	{
		dest[x] = str[x];
		x++;
		size_compare++;
	}
	dest[x] = '\0';
	return (ft_strlen(str));
}

void	ft_counting_map_size(t_all *all)
{
	int fd;
	char *temp;
	fd = open(all->map.name, O_RDONLY);
	if (fd < 0)
		exit(write(2, "Error\nSEGV: could not open the file\nMaybe the file is not existe or the permission does not allowed to open the file\n", 118));
	temp = get_next_line(fd);
	all->map.row_number = 0;
	all->map.big_size = 0;
	while (temp)
	{
		all->map.row_number++;
		if (all->map.big_size < ft_strlen(temp))
			all->map.big_size = ft_strlen(temp);
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}

void check_validaiton_name(char *name)
{
	char *temp;
	if (name == NULL || name[0] == '\0')
		exit(write(2, "Error\nSEGV: File name is empty or not valid", 43));
	temp = strrchr(name, '.');
	if (temp == NULL)
		exit(write(2,"Error\nThe file does not containe any extansion\n",48 ));
	if (strcmp(temp, ".cub"))
		exit(write(2, "Error\nSEGV\nThe File doe not contain the extansion '.cub'\nplease add the '.cub'extanson to the your map file", 102));
}

void read_map(t_all  *all)
{
	char *temp;	
	int fd;
	int i;

	i = 0;
	check_validaiton_name(all->map.name);
	ft_counting_map_size(all);
	fd = open(all->map.name, O_RDONLY);
	if (fd < 0)
		exit(write(2, "Error\nCould not open the file\nMaybe the file is not existe or the permission does not allowed to open the file", 104));
	temp = get_next_line(fd);
	if (temp == NULL)
		exit(write(2, "Error\nThe File \".cub\" is not containing anything\n", 50));
	all->map.map = calloc(sizeof(char *) * (all->map.row_number + 1), 1);
	while (temp)
	{
		all->map.map[i] = strdup(temp);
		free(temp);
		temp = get_next_line(fd);
		i++;
	}
	all->map.map[i] = NULL;
	close(fd);
}

char *return_elements(char *str)
{
	char *ptr;
	int i;
	int x;
	x = 0;
	i = 0;
	if (!str)
		return NULL;
	while (str[i] && str[i] == ' ')
		i++;
	ptr  = calloc((ft_strlen(str) - i) + 1 , 1);
	while (str[i] && str[i] != '\n')
	{
		ptr[x++] = str[i++];
	}
	ptr[x] = '\0';
	return (ptr);    
}

void put_it(t_all *all, char *name)
{
	if (strncmp(name, "EA", 2) == 0)
	{
		all->elem->ea = return_elements(name + 2);
	}
	if (strncmp(name, "SO", 2)==0)
	{
		all->elem->so = return_elements(name + 2);
	}
	if (strncmp(name, "NO", 2)==0)
	{
		all->elem->no = return_elements(name + 2);
	}
	if (strncmp(name, "WE", 2)==0)
	{
		all->elem->we = return_elements(name + 2);
	}
	if (strncmp(name, "F", 1) == 0)
	{
		all->elem->f_temp = return_elements(name + 1);
	}
	if (strncmp(name, "C", 1) == 0)
	{
		all->elem->c_temp = return_elements(name + 1);
	}
}

void ft_put_map(char *key, char *name, int *x)
{
	int i;
	i = 0;


	ft_strlcpy(key, name, ft_strlen(name));
	free(name);
	//free(name);
	*x = *x + 1;

}

void init(char **use, t_all *all)
{
	int i = 0;
	while (i < all->map.row_number)
	{
		use[i] = calloc(sizeof(char) *(all->map.big_size + 1), 1);
		i++;
	}
}

int all_is_space(char *s)
{
	int i;
	i =0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void put_them_in_the_place(t_all *all)
{
	int elements;
	int i;
	int x;
	int a;
	int ok;
	ok = 0;
	x = 0;

	a = 0;
	elements = 0;
	all->elem = calloc(sizeof(t_elem), 1);
	all->map.use = calloc(sizeof(char *) * (1 + all->map.row_number), 1);
	all->map.use[all->map.row_number] = NULL;
	init(all->map.use, all);
	i = 0;
	while (all->map.map[i])
	{
		if (elements < 6)
		{
			if (all->map.map[i][0] == '\n')
				i++;
			else 
			{
				put_it(all, all->map.map[i]);
				elements++;
				i++;
			}
		}
		else if (all->map.map[i][0] == '\n' && x == 0)
		{
			i++;
		}
		else
		{
			if (ok == 0 && (all->map.map[i][0] == '\n' || all_is_space(all->map.map[i]) == 0))
			{
				i++;
			}
			else
			{
				ft_put_map(all->map.use[a], all->map.map[i], &a);
				x = 1;
				i++;
				ok = 1;
			}
		}
	}
	free(all->map.use[a]);
	all->map.use[a] = NULL;
	if ( !all->elem->ea  || !all->elem->we  || !all->elem->c_temp  ||!all->elem->f_temp  ||!all->elem->no  ||!all->elem->so)
	    exit(write(2,  "Error\nSome elements of the map is not valid\nOr they are not puted in their right place\nPleasee make sure the everything is in its place\n", 130));


}

void check_textures(t_all *all)
{
	all->data.mlx_instance = mlx_init();
	all->tool.ea = mlx_xpm_file_to_image(all->data.mlx_instance, all->elem->ea, &all->data.ea.text_width, &all->data.ea.text_height);
	all->tool.no = mlx_xpm_file_to_image(all->data.mlx_instance, all->elem->no, &all->data.no.text_width, &all->data.no.text_height);
	all->tool.we = mlx_xpm_file_to_image(all->data.mlx_instance, all->elem->we, &all->data.we.text_width, &all->data.we.text_height);
	all->tool.so = mlx_xpm_file_to_image(all->data.mlx_instance, all->elem->so, &all->data.so.text_width, &all->data.so.text_height);
	if (!all->tool.ea || !all->tool.no || !all->tool.we || !all->tool.so)
		exit(write(2, "Error\nOops!\nSomething does not wotk as expected\nMaybe the texteurs are not valid or they are not exis\nOr their contant is not correct\nPlease make sure that everyhting is correct\nThank you", 180));
	all->data.ea.text =  mlx_get_data_addr(all->tool.ea, &all->data.ea.bit_per_pixel, &all->data.ea.text_line_lenght, &all->data.ea.text_endian);
	all->data.so.text = mlx_get_data_addr(all->tool.so, &all->data.so.bit_per_pixel, &all->data.so.text_line_lenght, &all->data.so.text_endian);
	all->data.no.text = mlx_get_data_addr(all->tool.no, &all->data.no.bit_per_pixel, &all->data.no.text_line_lenght, &all->data.no.text_endian);
	all->data.we.text = mlx_get_data_addr(all->tool.we, &all->data.we.bit_per_pixel, &all->data.we.text_line_lenght, &all->data.we.text_endian);
	if (!all->data.ea.text || !all->data.so.text | !all->data.no.text | !all->data.we.text)
		exit(write(2, " Error\nOpps something does not work as expacted\n", 48));

}

void check_ele(char **str)
{
	t_l *l;

	l = calloc(sizeof(t_l), 1);
	while (str[l->a])
	{
		l->i = 0;
		while (str[l->a][l->i])
		{
			if (str[l->a][l->i] == 'N' || str[l->a][l->i] == 'S' || str[l->a][l->i] == 'W' || str[l->a][l->i] == 'E')
				l->player++;
			else if (str[l->a][l->i] == '1')
				l->wall++;
			else if (str[l->a][l->i] == '0')
					l->space++;	
			else if (str[l->a][l->i] == ' ' || str[l->a][l->i] == '\n')
			{
				l->i++;
				continue;
			}
			else
				exit(write(2, "Error\nA character is not valid\n", 32));
			l->i++;
		}
		
		l->a++;
	}
	if (l->player != 1 || l->wall == 0 || l->space == 0)
		exit(write(2,"Error\nMmmmm! there is a problem in characters\n", 46));
	free(l);
}

void ft_help_my_flood_fill(char **map, int i, int x)
{
	if (map[i + 1][x] == '\n' || map[i + 1][x] == '\0' || map[i + 1][x] == ' ')
		exit(write(2, "Error\nThe Map is not rounded with walls\n", 40));
	else if (map[i - 1][x] == '\0' || map[i - 1][x] == ' ')
		exit(write(2, "Error\nThe Map is not rounded with walls444\n", 44));
	else if (map[i][x - 1] == '\n' || map[i][x - 1] == '\0' || map[i][x - 1] == ' ')
		exit(write(2, "Error\nThe Map is not rounded with walls\n", 40));
 	else if (map[i][x + 1] == '\n' || map[i][x + 1] == '\0' || map[i][x + 1] == ' ')
		exit(write(2, "Error\nThe Map is not rounded with walls\n", 40));			
}

void my_flood_fill(char **map)
{
	int i;
	int x;

	i = 1;
	x = 0;

	while (map[i + 1])
	{
		x = 0;
		while (map[i][x])
		{
			if (map[i][x] == '0' || map[i][x] == 'W' || map[i][x] == 'E' || map[i][x] == 'S' || map[i][x] == 'N')
				ft_help_my_flood_fill(map, i, x);
			x++;
		}
		i++;
	}
	x = 0;
	while (map[i][x])
	{
		if (map[i][x] != '1' && map[i][x] != ' ' && map[i][x] != '\n')
			exit(write(2, "Error\nthe map is not closed with the walls\n", 44));
		x++;
	}
}

void check_map(char **map)
{
	int i;
	int y;

	i = 0;
	y = 1;
	check_ele(map);
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != '\n' && map[0][i] != ' ')
			exit(write(2, "error\nWait! wait! the wall is not closed\nPlease make sure everything is correct\n", 81));
		i++;
	}
	my_flood_fill(map);
}

// void check_rgb_is_valid(t_all *all)
// {

// }

// void handle_rgbt(t_all *all)
// {
// 	check_rgb_is_valid(all->elem->c_temp);
// }
void is_they_valid(t_all *all)
{
	check_map(all->map.use);
	check_textures(all);
//	handle_rgbt(all);
	all->data.map = all->map.use;
}

void ft_parsing(t_all *all, char *av)
{
	all->map.name = av;
	read_map(all);
	put_them_in_the_place(all);
	is_they_valid(all);
}