/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:29:33 by labdello          #+#    #+#             */
/*   Updated: 2024/09/23 16:29:52 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_config *config, t_philo *philo_lst, char **args)
{
	(void)args;
	(void)philo_lst;
	(void)config;
	return ;
}

int	args_validation(char **args)
{
	size_t		i;
	long long	n;

	i = 0;
	while (args[i] != NULL)
	{
		if (!ft_isnbr(args[i]) || ft_strlen(args[i]) > 11)
			return (0);
		n = ft_atoll(args[i]);
		if (n > INT_MAX || n < INT_MIN)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_config	config;
	t_philo		*philo_lst;

	philo_lst = NULL;
	if (ac < 5 || ac > 6 || !args_validation(av + 1))
		return (1);
	init_philo(&config, philo_lst, av + 1);
	return (0);
}
