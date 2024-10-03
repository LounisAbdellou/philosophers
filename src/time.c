/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:58 by labdello          #+#    #+#             */
/*   Updated: 2024/10/04 17:34:00 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_action_time(t_param *params, size_t	initial_time)
{
	size_t		timestamp;
	long long	time_left;

	timestamp = get_time_diff(params->last_ate);
	time_left = get_time_diff(params->config->start_ms) - timestamp;
	if (time_left < (long long)initial_time && time_left >= 0)
		return ((size_t)time_left);
	else if (time_left < (long long)initial_time && time_left < 0)
		return (0);
	return (initial_time);
}

size_t	get_time_diff(size_t start_ms)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_ms);
}
