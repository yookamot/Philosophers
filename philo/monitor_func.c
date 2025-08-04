/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:32:03 by yookamot          #+#    #+#             */
/*   Updated: 2025/07/17 23:33:04 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_death(t_data *data, int i, size_t now)
{
	pthread_mutex_unlock(&data->meal_mutex);
	pthread_mutex_lock(&data->dead_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_lock(&data->write_mutex);
	printf("%zu %d died\n", now - data->start_time, data->philos[i].id);
	pthread_mutex_unlock(&data->write_mutex);
}

void	*monitor_func(void *arg)
{
	t_data	*data;
	int		i;
	size_t	now;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			pthread_mutex_lock(&data->meal_mutex);
			now = get_current_time();
			if (now - data->philos[i].last_meal > (size_t)data->time_to_die)
				return (handle_death(data, i, now), NULL);
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		if (data->must_eat > 0)
		{
			if (data->all_ate)
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
