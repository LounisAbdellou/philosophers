/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:52:08 by labdello          #+#    #+#             */
/*   Updated: 2024/09/30 18:51:17 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(char *msg, size_t time_ms, int id, t_config *config)
{
	pthread_mutex_lock(&(config->print_mutex));
	printf(msg, time_ms, id);
	pthread_mutex_unlock(&(config->print_mutex));
}

void	thinking(int id, size_t time_ms, t_config *config)
{
	size_t	timestamp;

	timestamp = get_time_diff(config->start_ms);
	print_action("%lu %d is thinking\n", timestamp, id, config);
	usleep(time_ms * 1000);
}

void	sleeping(int id, t_config *config)
{
	size_t	timestamp;

	timestamp = get_time_diff(config->start_ms);
	print_action("%lu %d is sleeping\n", timestamp, id, config);
	usleep(config->time_to_sleep * 1000);
}

void	eating(int id, pthread_mutex_t forks[2], t_config *config)
{
	size_t	timestamp;

	(void)forks;
	timestamp = get_time_diff(config->start_ms);
	print_action("%lu %d is eating\n", timestamp, id, config);
	usleep(config->time_to_eat * 1000);
}
