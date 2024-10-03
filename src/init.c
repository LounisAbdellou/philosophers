/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:52:47 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/04 23:07:40 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_config(t_config *config, char **args, int arg_count)
{
	config->philo_c = ft_atoi(args[1]);
	config->t_die = ft_atoi(args[2]);
	config->t_eat = ft_atoi(args[3]);
	config->t_sleep = ft_atoi(args[4]);
	if (arg_count == 6)
		config->tm_eat = ft_atoi(args[5]);
	else
		config->tm_eat = -1;
	config->start_ms = get_time_diff(0);
}

void	init_shared_vars(t_config *conf, t_param **params, int *dead, int *eat)
{
	int	i;
	int	id;

	i = 0;
	*dead = 0;
	*eat = 0;
	while (i < conf->philo_c)
	{
		id = (*params)[i].id;
		(*params)[i].has_dead = dead;
		(*params)[i].eat_c = eat;
		if (id >= (*params)[i].config->philo_c)
			(*params)[i].r_fork = &((*params)[0].l_fork);
		else
			(*params)[i].r_fork = &((*params)[id].l_fork);
		i++;
	}
}

int	init_philo(t_config *config, t_param **params)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(config->eat_m), NULL);
	pthread_mutex_init(&(config->death_m), NULL);
	pthread_mutex_init(&(config->print_m), NULL);
	pthread_mutex_init(&(config->stop_m), NULL);
	*params = ft_calloc(config->philo_c + 1, sizeof(t_param));
	if (!(*params))
		return (0);
	while (i < config->philo_c)
	{
		(*params)[i].id = i + 1;
		(*params)[i].config = config;
		(*params)[i].r_fork = NULL;
		pthread_mutex_init(&((*params)[i].l_fork), NULL);
		i++;
	}
	return (1);
}
