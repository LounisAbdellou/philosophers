/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:26:01 by labdello          #+#    #+#             */
/*   Updated: 2024/10/03 14:45:23 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*obs_routine(void *ptr)
{
	int			i;
	int			done;
	t_param		*params;
	t_config	*config;

	i = 0;
	params = (t_param *)ptr;
	config = params->config;
	while (1)
	{
		pthread_mutex_lock(&(params->config->eat_mutex));
		done = *(params->eat_count) == config->philo_count * config->time_must_eat;
		pthread_mutex_unlock(&(params->config->eat_mutex));
		if (*params->has_dead == 1 || done)
		{	
			while (i < params->config->philo_count)
			{
				pthread_detach(params->philos[i]);
				i++;
			}
			return (pthread_mutex_unlock(&(params->config->eat_mutex)), NULL);
		}
	}
	return (NULL);
}

void	assign_forks(pthread_mutex_t (*assigned_forks)[2], t_param *params)
{
	(*assigned_forks)[E_LEFT] = params->forks[params->id - 1];
	if (params->id >= params->config->philo_count)
		(*assigned_forks)[E_RIGHT] = params->forks[0];
	else
		(*assigned_forks)[E_RIGHT] = params->forks[params->id];
}

void	*philos_routine(void *ptr)
{
	int				this_eat_count;
	t_param			*params;
	pthread_mutex_t	assigned_forks[2];

	this_eat_count = 0;
	params = (t_param *)ptr;
	assign_forks(&assigned_forks, params);
	if (params->id % 2 == 0)
		usleep(params->config->time_to_eat * 1000);
	while (1)
	{
		eating(params, params->config->time_to_eat, assigned_forks);
		if (this_eat_count++ < params->config->time_must_eat)
		{
			pthread_mutex_lock(&(params->config->eat_mutex));
			*(params->eat_count) += 1;
			pthread_mutex_unlock(&(params->config->eat_mutex));
		}
		sleeping(params, params->config->time_to_sleep);
	}	
	return (NULL);
}
