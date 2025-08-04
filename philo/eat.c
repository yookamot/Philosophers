/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:58:57 by yookamot          #+#    #+#             */
/*   Updated: 2025/07/17 23:35:06 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_all_ate(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->meal_mutex);
	while (i < philo->data->number_of_philos)
	{
		if (philo->data->philos[i].meals_eaten < philo->data->must_eat)
			return (pthread_mutex_unlock(&philo->data->meal_mutex), 0);
		i++;
	}
	philo->data->all_ate = 1;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("[optional] All philosophers have eaten %d times\n",
		philo->data->must_eat);
	pthread_mutex_unlock(&philo->data->write_mutex);
	return (1);
}

int	eat(t_philo *philo)
{
	if (is_dead(philo->data) || philo->data->all_ate)
		return (0);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->data->must_eat > 0 && !philo->data->all_ate
		&& handle_all_ate(philo))
		return (0);
	usleep(philo->data->time_to_eat * 1000);
	return (1);
}
