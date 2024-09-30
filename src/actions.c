/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:52:08 by labdello          #+#    #+#             */
/*   Updated: 2024/10/02 14:40:47 by solid_42         ###   ########.fr       */
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

void	sleeping(int id, size_t time, t_config *config)
{
	size_t	timestamp;

	timestamp = get_time_diff(config->start_ms);
	print_action("%lu %d is sleeping\n", timestamp, id, config);
	usleep(time * 1000);
}

void	eating(int id, size_t time, pthread_mutex_t forks[2], t_config *config)
{
	size_t	timestamp;

	(void)forks;
	/* pthread_mutex_lock(&forks[E_LEFT]); */
	timestamp = get_time_diff(config->start_ms);
	/* print_action("%lu %d has taken a fork\n", timestamp, id, config); */
	/* pthread_mutex_lock(&forks[E_RIGHT]); */
	/* timestamp = get_time_diff(config->start_ms); */
	/* print_action("%lu %d has taken a fork\n", timestamp, id, config); */
	print_action("%lu %d is eating\n", timestamp, id, config);
	usleep(time * 1000);
	/* pthread_mutex_unlock(&forks[E_LEFT]); */
	/* pthread_mutex_unlock(&forks[E_RIGHT]); */
}
