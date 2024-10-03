/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:29:33 by labdello          #+#    #+#             */
/*   Updated: 2024/10/07 18:44:55 by labdello         ###   ########.fr       */
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

int	philosophers(t_config *config, t_param *params)
{
	int			i;
	int			has_dead;
	int			eat_c;

	i = 0;
	init_shared_vars(config, &params, &has_dead, &eat_c);
	while (i < config->philo_c)
	{
		if (pthread_create(&(params[i].thread), NULL,
				&philos_routine, &params[i]) != 0)
			return (free(params), 0);
		i++;
	}
	while (i > 0)
		pthread_join(params[--i].thread, NULL);
	return (free(params), 1);
}

int	main(int ac, char **av)
{
	t_config		config;
	t_param			*params;

	if (ac < 5 || ac > 6 || !args_validation(av + 1))
		return (1);
	init_config(&config, av, ac);
	if (!init_philo(&config, &params))
		return (1);
	if (!philosophers(&config, params))
		return (1);
	return (0);
}
