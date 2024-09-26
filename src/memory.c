/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:29:23 by labdello          #+#    #+#             */
/*   Updated: 2024/09/27 16:33:05 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_bzero(void *ptr, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	if (n != 0 && size > SIZE_MAX / n)
		return (NULL);
	ptr = malloc(n * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, n * size);
	return (ptr);
}
