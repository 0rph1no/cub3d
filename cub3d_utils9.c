/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 02:33:32 by abouzanb          #+#    #+#             */
/*   Updated: 2023/05/15 02:33:33 by abouzanb         ###   ########.fr       */
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

void	count_str(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i != 3)
		exit(write(2, "Error\nIn RGB", 13));
}

void	initilaized(t_all *all, char **f, char **c)
{
	t_elem	l;

	l.ctemp1 = ft_atoi(c[0]);
	l.ctemp2 = ft_atoi(c[1]);
	l.ctemp3 = ft_atoi(c[2]);
	l.ftemp1 = ft_atoi(f[0]);
	l.ftemp2 = ft_atoi(f[1]);
	l.ftemp3 = ft_atoi(f[2]);
	all->data.f_colour = (l.ftemp1 * 65536) + (l.ftemp2 * 256) + l.ftemp3;
	all->data.c_colour = (l.ctemp1 * 65536) + (l.ctemp2 * 256) + l.ctemp3;
}
