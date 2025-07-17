/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2darray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahroug <adahroug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:04:51 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/07 14:05:15 by adahroug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char **src)
{
	int	count;

	count = 0;
	while (src[count] != NULL)
		count++;
	return (count);
}

char	**allocate_copy(int count)
{
	char	**copy;

	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	copy[count] = NULL;
	return (copy);
}

char	**malloc_2d_copy(char **src)
{
	int		count;
	int		i;
	char	**copy;
	int		j;

	i = 0;
	count = count_lines(src);
	copy = allocate_copy(count);
	while (i < count)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
		{
			j = i - 1;
			while (j >= 0)
				free(copy[j--]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}
