/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:26:44 by labdello          #+#    #+#             */
/*   Updated: 2024/10/03 12:47:52 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(char *msg, size_t time, int id, t_config *config)
{
	pthread_mutex_lock(&(config->print_mutex));
	printf(msg, time, id);
	pthread_mutex_unlock(&(config->print_mutex));
}

void	thinking(int id, size_t time, t_config *config)
{
	size_t	timestamp;

	timestamp = get_time_diff(config->start_ms);
	print_action("%lu %d is thinking\n", timestamp, id, config);
	usleep(time * 1000);
}

void	sleeping(t_param *params, size_t time)
{
	size_t	timestamp;

	timestamp = get_time_diff(params->config->start_ms);
	print_action("%lu %d is sleeping\n", timestamp, params->id, params->config);
	usleep(time * 1000);
}

void	eating(t_param *params, size_t time, pthread_mutex_t forks[2])
{
	int		id;
	size_t	timestamp;

	id = params->id;
	pthread_mutex_lock(&forks[E_LEFT]);
	timestamp = get_time_diff(params->config->start_ms);
	print_action("%lu %d has taken a fork\n", timestamp, id, params->config);
	pthread_mutex_lock(&forks[E_RIGHT]);
	timestamp = get_time_diff(params->config->start_ms);
	print_action("%lu %d has taken a fork\n", timestamp, id, params->config);
	print_action("%lu %d is eating\n", timestamp, id, params->config);
	usleep(time * 1000);
	pthread_mutex_unlock(&forks[E_LEFT]);
	pthread_mutex_unlock(&forks[E_RIGHT]);
}
