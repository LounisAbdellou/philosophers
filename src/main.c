/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:29:33 by labdello          #+#    #+#             */
/*   Updated: 2024/09/30 18:51:43 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_validation(char **args)
{
	size_t		i;
	long long	n;

	i = 0;
	while (args[i] != NULL)
	{
		if (!ft_isnbr(args[i]))
			return (0);
		n = ft_atoll(args[i]);
		if (n > INT_MAX || n < 1)
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_config *c, t_param **pa, pthread_mutex_t **f, pthread_t **ph)
{
	int	i;

	i = 0;
	*pa = ft_calloc(c->philo_count + 1, sizeof(t_param));
	if (!(*pa))
		return (0);
	*ph = ft_calloc(c->philo_count + 1, sizeof(pthread_t));
	if (!(*ph))
		return (free(*pa), 0);
	*f = ft_calloc(c->philo_count + 1, sizeof(pthread_mutex_t));
	if (!(*f))
		return (free(*pa), free(*ph), 0);
	while (i < c->philo_count)
	{
		pthread_mutex_init(&(*f)[i], NULL);
		i++;
	}
	while (i >= 0)
	{
		(*pa)[i].id = i + 1;
		(*pa)[i].forks = *f;
		(*pa)[i].config = c;
		i--;
	}
	return (1);
}

void	*philos_routine(void *ptr)
{
	t_param			*params;
	pthread_mutex_t	assigned_forks[2];

	params = (t_param *)ptr;
	assigned_forks[E_LEFT] = params->forks[params->id - 1];
	if (params->id >= params->config->philo_count)
		assigned_forks[E_RIGHT] = params->forks[0];
	else
		assigned_forks[E_RIGHT] = params->forks[params->id];
	while (1)
	{
		eating(params->id, assigned_forks, params->config);
		break ;
	}
	return (NULL);
}

int	philosophers(t_config *config, t_param *params, pthread_t *philos)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(config->print_mutex), NULL);
	while (i < config->philo_count)
	{
		if (pthread_create(&philos[i], NULL, &philos_routine, &params[i]) != 0)
			return (free(philos), free(params), 0);
		i++;
	}
	while (i > 0)
		if (pthread_join(philos[--i], NULL) != 0)
			return (free(philos), free(params), 0);
	return (free(philos), free(params), 1);
}

int	main(int ac, char **av)
{
	t_config		config;
	t_param			*params;
	pthread_t		*philos;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6 || !args_validation(av + 1))
		return (1);
	config.philo_count = ft_atoi(av[1]);
	config.time_to_die = ft_atoi(av[2]);
	config.time_to_eat = ft_atoi(av[3]);
	config.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		config.time_must_eat = ft_atoi(av[5]);
	config.start_ms = get_time_diff(0);
	if (!init_philo(&config, &params, &forks, &philos))
		return (1);
	if (!philosophers(&config, params, philos))
		return (free(forks), 1);
	return (free(forks), 0);
}
