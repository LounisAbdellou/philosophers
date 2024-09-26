/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:30:49 by labdello          #+#    #+#             */
/*   Updated: 2024/09/30 18:51:42 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_config
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	unsigned long	start_ms;
	pthread_mutex_t	print_mutex;
}	t_config;

typedef struct s_param
{
	int				id;
	t_config		*config;
	pthread_mutex_t	*forks;
}	t_param;

typedef struct s_forks
{
	pthread_mutex_t	*available_forks;
	pthread_mutex_t	assigned_forks[2];
}	t_forks;

typedef enum e_fork_pos
{
	E_LEFT = 0,
	E_RIGHT = 1,
}	t_fork_pos;

// NUMBERS
int				ft_isnbr(char *str);
int				ft_atoi(char *str);
long long		ft_atoll(char *str);

// MEMORY
void			*ft_calloc(size_t n, size_t size);

// TIME
unsigned long	get_time_diff(unsigned long start_ms);

// ACTIONS
void			sleeping(int id, t_config *config);
void			eating(int id, pthread_mutex_t forks[2], t_config *config);
void			thinking(int id, unsigned long time_ms, t_config *config);

#endif
