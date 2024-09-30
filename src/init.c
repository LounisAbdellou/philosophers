/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solid_42 </var/spool/mail/solid_42>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:52:47 by solid_42          #+#    #+#             */
/*   Updated: 2024/10/02 15:10:48 by solid_42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_config(t_config *config, char **args, int arg_count)
{
	config->philo_count = ft_atoi(args[1]);
	config->time_to_die = ft_atoi(args[2]);
	config->time_to_eat = ft_atoi(args[3]);
	config->time_to_sleep = ft_atoi(args[4]);
	if (arg_count == 6)
		config->time_must_eat = ft_atoi(args[5]);
	else
		config->time_must_eat = -1;
	config->start_ms = get_time_diff(0);
}

void	init_shared_vars(t_config *conf, t_param **params, int *dead, int *done)
{
	int	i;

	i = 0;
	*dead = 0;
	*done = 0;
	while (i < (conf->philo_count + 1))
	{
		(*params)[i].has_dead = dead;
		(*params)[i].done_count = done;
		i++;
	}
}

int	init_philo(t_config *c, t_param **pa, pthread_mutex_t **f, pthread_t **ph)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(c->done_mutex), NULL);
	pthread_mutex_init(&(c->death_mutex), NULL);
	pthread_mutex_init(&(c->print_mutex), NULL);
	*pa = ft_calloc(c->philo_count + 2, sizeof(t_param));
	if (!(*pa))
		return (0);
	*ph = ft_calloc(c->philo_count + 1, sizeof(pthread_t));
	if (!(*ph))
		return (free(*pa), 0);
	*f = ft_calloc(c->philo_count + 1, sizeof(pthread_mutex_t));
	if (!(*f))
		return (free(*pa), free(*ph), 0);
	while (i < (c->philo_count + 1))
		pthread_mutex_init(&(*f)[i++], NULL);
	while (i >= 0)
	{
		(*pa)[i].id = i + 1;
		(*pa)[i].forks = *f;
		(*pa)[i--].config = c;
	}
	return (1);
}
