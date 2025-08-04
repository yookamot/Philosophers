/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:02:31 by yookamot          #+#    #+#             */
/*   Updated: 2025/07/19 18:11:51 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	is_dead(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->dead_mutex);
	status = data->someone_died;
	pthread_mutex_unlock(&data->dead_mutex);
	return (status);
}

void	print_action(t_philo *philo, const char *message)
{
	size_t	timestamp;

	if (philo->data->all_ate)
		return ;
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!is_dead(philo->data))
	{
		timestamp = get_current_time() - philo->data->start_time;
		printf("%zu %d %s\n", timestamp, philo->id, message);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

static void	sleep_and_think(t_philo *philo)
{
	if (is_dead(philo->data) || philo->data->all_ate)
		return ;
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	print_action(philo, "is thinking");
}

void	*philo_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philos == 1)
		return (handle_single_philo(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo->data) && !philo->data->all_ate)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		if (philo->data->all_ate || !eat(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (NULL);
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep_and_think(philo);
		usleep(300);
	}
	return (NULL);
}
