/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:30:49 by labdello          #+#    #+#             */
/*   Updated: 2024/10/07 19:36:30 by labdello         ###   ########.fr       */
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
	int				philo_c;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				tm_eat;
	size_t			start_ms;
	pthread_mutex_t	stop_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	death_m;
	pthread_mutex_t	eat_m;
}	t_config;

typedef struct s_obs_param
{
	int				*has_dead;
	size_t			*last_ate;
	pthread_mutex_t	stop_m;
}	t_obs_param;

typedef struct s_param
{
	int				id;
	int				*eat_c;
	int				*has_dead;
	size_t			last_ate;
	t_config		*config;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
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

// INIT
int				init_philo(t_config *c, t_param **params);
void			init_config(t_config *config, char **args, int arg_count);
void			init_shared_vars(t_config *conf, t_param **params, int *dead,
					int *eat);

// NUMBERS
int				ft_isnbr(char *str);
int				ft_atoi(char *str);
long long		ft_atoll(char *str);

// MEMORY
void			*ft_calloc(size_t n, size_t size);

// TIME
size_t			get_time_diff(size_t start_ms);
size_t			get_action_time(t_param *params, size_t	initial_time);

// ACTIONS
void			print_action(char *msg, size_t time, t_param *params);
void			f_print_action(char *msg, size_t time, t_param *params);
void			thinking(t_param *params);
void			sleeping(t_param *params, size_t time);
void			eating(t_param *params, size_t time);

// ROUTINES
void			*obs_routine(void *ptr);
void			*philos_routine(void *ptr);
int				has_dead(t_param *params);
int				has_finished(t_param *params);

#endif
