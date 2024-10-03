/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:39:36 by labdello          #+#    #+#             */
/*   Updated: 2024/10/07 18:39:54 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(char *msg, size_t time, t_param *params)
{
	if (has_dead(params) || has_finished(params))
		return ;
	pthread_mutex_lock(&(params->config->print_m));
	printf(msg, time, params->id);
	pthread_mutex_unlock(&(params->config->print_m));
}

void	f_print_action(char *msg, size_t time, t_param *params)
{
	pthread_mutex_lock(&(params->config->print_m));
	printf(msg, time, params->id);
	pthread_mutex_unlock(&(params->config->print_m));
}
