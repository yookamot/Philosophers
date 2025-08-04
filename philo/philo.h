/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:44:06 by yookamot          #+#    #+#             */
/*   Updated: 2025/07/19 18:05:32 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	size_t				last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	size_t				start_time;
	int					someone_died;
	int					all_ate;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		meal_mutex;

	t_philo				*philos;
	pthread_t			monitor;

}						t_data;

int						init_data(int argc, char **argv, t_data *data);
int						init_mutex(t_data *data);
int						init_philos(t_data *data);
int						error_mutex(t_data *data, int i, int flag);
void					*philo_func(void *arg);
void					*monitor_func(void *arg);
int						eat(t_philo *philo);
int						is_dead(t_data *data);
void					print_action(t_philo *philo, const char *message);
size_t					get_current_time(void);
void					cleanup(t_data *data);

#endif