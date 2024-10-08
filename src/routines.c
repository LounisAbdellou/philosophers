/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:26:01 by labdello          #+#    #+#             */
/*   Updated: 2024/10/08 10:30:27 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_dead(t_param *params)
{
	pthread_mutex_lock(&(params->config->death_m));
	if ((*params->has_dead))
		return (pthread_mutex_unlock(&(params->config->death_m)), 1);
	pthread_mutex_unlock(&(params->config->death_m));
	return (0);
}

int	has_finished(t_param *params)
{
	t_config	*config;

	config = params->config;
	pthread_mutex_lock(&(params->config->eat_m));
	if (*(params->eat_c) == config->philo_c * config->tm_eat)
		return (pthread_mutex_unlock(&(params->config->eat_m)), 1);
	pthread_mutex_unlock(&(params->config->eat_m));
	return (0);
}

void	*death_check(void *ptr)
{
	size_t	timestamp;
	t_param	*params;

	params = (t_param *)ptr;
	while (!has_dead(params) && !has_finished(params))
	{
		pthread_mutex_lock(&(params->config->stop_m));
		timestamp = get_time_diff(params->last_ate);
		pthread_mutex_unlock(&(params->config->stop_m));
		if (timestamp < ((size_t)params->config->t_die) + 5)
			continue ;
		timestamp = get_time_diff(params->config->start_ms);
		pthread_mutex_lock(&(params->config->death_m));
		if ((*params->has_dead))
			return (pthread_mutex_unlock(&(params->config->death_m)), NULL);
		*(params->has_dead) = 1;
		f_print_action("%lu %d died\n", timestamp, params);
		pthread_mutex_unlock(&(params->config->death_m));
		break ;
	}
	return (NULL);
}

void	*philos_routine(void *ptr)
{
	int				this_eat_count;
	t_param			*p;
	pthread_t		observer;

	this_eat_count = 0;
	p = (t_param *)ptr;
	p->last_ate = get_time_diff(0);
	if (p->config->philo_c % 2 != 0 && p->id == p->config->philo_c)
		usleep(p->config->t_eat * 1000);
	while (!has_dead(p) && !has_finished(p))
	{
		pthread_create(&observer, NULL, &death_check, p);
		if (this_eat_count != p->config->tm_eat)
			eating(p, p->config->t_eat);
		if (this_eat_count++ < p->config->tm_eat)
		{
			pthread_mutex_lock(&(p->config->eat_m));
			*(p->eat_c) += 1;
			pthread_mutex_unlock(&(p->config->eat_m));
		}
		sleeping(p, p->config->t_sleep);
		pthread_detach(observer);
		thinking(p);
	}
	return (NULL);
}
