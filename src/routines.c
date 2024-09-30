/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:57:12 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/02 15:13:26 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*obs_routine(void *ptr)
{
	/* int		i; */
	t_param	*params;

	/* i = 0; */
	params = (t_param *)ptr;
	while (1)
	{
		/* if (*params->has_dead == 1) */
		/* {	 */
		/* 	while (i < params->config->philo_count) */
		/* 	{ */
		/* 		pthread_detach(params->philos[i]); */
		/* 		i++; */
		/* 	} */
		/* 	break ; */
		/* } */
		printf("test\n");
		printf("%p\n", params->done_count);
		/* if (*(params->done_count) == params->config->philo_count) */
		/* 	break ; */
	}
	return (NULL);
}

void	*philos_routine(void *ptr)
{
	int				routine_count;
	t_param			*params;
	pthread_mutex_t	assigned_forks[2];

	params = (t_param *)ptr;
	routine_count = params->config->time_must_eat;
	assigned_forks[E_LEFT] = params->forks[params->id - 1];
	if (params->id >= params->config->philo_count)
		assigned_forks[E_RIGHT] = params->forks[0];
	else
		assigned_forks[E_RIGHT] = params->forks[params->id];
	if (params->id % 2 == 0)
		usleep(params->config->time_to_eat * 1000);
	while (1)
	{
		if (routine_count == 0)
			break ;
		eating(params->id, params->config->time_to_eat, assigned_forks,
			params->config);
		if (params->config->time_must_eat != -1)
			routine_count--;
	}	
	/* pthread_mutex_lock(&(params->config->done_mutex)); */
	/* *(params->done_count) += 1; */
	/* pthread_mutex_unlock(&(params->config->done_mutex)); */
	return (NULL);
}
