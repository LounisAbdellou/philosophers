/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:29:33 by labdello          #+#    #+#             */
/*   Updated: 2024/10/03 13:05:49 by labdello         ###   ########.fr       */
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

int	philosophers(t_config *config, t_param *params, pthread_t *philos)
{
	int			i;
	int			has_dead;
	int			eat_count;
	pthread_t	observer;

	i = 0;
	init_shared_vars(config, &params, &has_dead, &eat_count);
	while (i < config->philo_count)
	{
		if (pthread_create(&philos[i], NULL, &philos_routine, &params[i]) != 0)
			return (free(philos), free(params), 0);
		i++;
	}
	params[i].philos = philos;
	if (pthread_create(&observer, NULL, &obs_routine, &params[i]) != 0)
		return (free(philos), free(params), 0);
	pthread_join(observer, NULL);
	while (i > 0)
		pthread_join(philos[--i], NULL);
	return (free(philos), free(params), 1);
}

int	main(int ac, char **av)
{
	t_config		config;
	t_param			*params;
	pthread_t		*philos;
	pthread_mutex_t	*forks;

	init_config(&config, av, ac);
	if (ac < 5 || ac > 6 || !args_validation(av + 1))
		return (1);
	if (!init_philo(&config, &params, &forks, &philos))
		return (1);
	if (!philosophers(&config, params, philos))
		return (free(forks), 1);
	return (free(forks), 0);
}
