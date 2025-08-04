/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:36:57 by yookamot          #+#    #+#             */
/*   Updated: 2025/06/28 17:38:36 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_mutex(t_data *data, int i, int flag)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&data->forks[j]);
		j++;
	}
	free(data->forks);
	if (flag > 1)
		pthread_mutex_destroy(&data->write_mutex);
	if (flag > 2)
		pthread_mutex_destroy(&data->dead_mutex);
	if (flag > 3)
		pthread_mutex_destroy(&data->meal_mutex);
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (error_mutex(data, i, 0));
		i++;
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	if (!init_forks(data))
		return (0);
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (error_mutex(data, data->number_of_philos, 1));
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		return (error_mutex(data, data->number_of_philos, 2));
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (error_mutex(data, data->number_of_philos, 3));
	return (1);
}
