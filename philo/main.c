/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:46:53 by yookamot          #+#    #+#             */
/*   Updated: 2025/07/17 23:55:43 by yookamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	is_dead_or_all_ate(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->dead_mutex);
	if (result)
		return (1);
	pthread_mutex_lock(&data->meal_mutex);
	result = data->all_ate;
	pthread_mutex_unlock(&data->meal_mutex);
	return (result);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!init_data(argc, argv, &data))
		return (1);
	if (!init_philos(&data))
		return (1);
	i = 0;
	data.start_time = get_current_time();
	while (i < data.number_of_philos)
	{
		data.philos[i].last_meal = data.start_time;
		pthread_create(&data.philos[i].thread, NULL, philo_func,
			&data.philos[i]);
		i++;
	}
	pthread_create(&data.monitor, NULL, monitor_func, &data);
	while (!is_dead_or_all_ate(&data))
		usleep(1000);
	i = 0;
	while (i < data.number_of_philos)
		pthread_join(data.philos[i++].thread, NULL);
	pthread_join(data.monitor, NULL);
	cleanup(&data);
	return (0);
}
