/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:26:44 by labdello          #+#    #+#             */
/*   Updated: 2024/10/07 19:56:39 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_param *params)
{
	size_t	timestamp;

	timestamp = get_time_diff(params->config->start_ms);
	print_action("%lu %d is thinking\n", timestamp, params);
}

void	sleeping(t_param *params, size_t time)
{
	size_t	timestamp;

	timestamp = get_time_diff(params->config->start_ms);
	print_action("%lu %d is sleeping\n", timestamp, params);
	usleep(time * 1000);
}

void	take_forks(t_param *params)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (params->id % 2 == 0)
	{
		first = params->r_fork;
		second = &params->l_fork;
	}
	else
	{
		first = &params->l_fork;
		second = params->r_fork;
	}
	pthread_mutex_lock(first);
	print_action("%lu %d has taken a fork\n",
		get_time_diff(params->config->start_ms), params);
	if (params->config->philo_c == 1)
	{
		usleep(params->config->t_die * 1000);
		return ;
	}
	pthread_mutex_lock(second);
	print_action("%lu %d has taken a fork\n",
		get_time_diff(params->config->start_ms), params);
}

void	eating(t_param *params, size_t time)
{
	take_forks(params);
	print_action("%lu %d is eating\n",
		get_time_diff(params->config->start_ms), params);
	pthread_mutex_lock(&(params->config->stop_m));
	params->last_ate = get_time_diff(0);
	pthread_mutex_unlock(&(params->config->stop_m));
	usleep(time * 1000);
	if (params->id % 2 == 0)
	{
		pthread_mutex_unlock(params->r_fork);
		pthread_mutex_unlock(&params->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&params->l_fork);
		pthread_mutex_unlock(params->r_fork);
	}
}
