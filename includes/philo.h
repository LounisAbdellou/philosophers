/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:30:49 by labdello          #+#    #+#             */
/*   Updated: 2024/09/23 16:28:42 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_fork_pos
{
	E_LEFT = 0,
	E_RIGHT = 1,
}	t_fork_pos;

typedef struct s_fork
{
	int				index;
	int				is_clean;
	pthread_mutex_t	*mutex;
	struct s_fork	*next;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		*thread;
	struct s_fork	*forks;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

typedef struct s_config
{
	int	eat_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_config;

int			ft_isnbr(char *str);
int			ft_atoi(char *str);
size_t		ft_strlen(char *str);
long long	ft_atoll(char *str);

#endif
