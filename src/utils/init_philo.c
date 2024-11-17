/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:44:36 by akloster          #+#    #+#             */
/*   Updated: 2024/11/17 20:53:10 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&((data->fork)[i]), NULL))
			return (ft_error("Error: mutex init. failed"));
	}
	if (pthread_mutex_init(data->meal_lock, NULL)
		|| pthread_mutex_init(data->print_lock, NULL)
		|| pthread_mutex_init(data->stop_lock, NULL)
		|| pthread_mutex_init(data->rw_lock, NULL)
		|| pthread_mutex_init(data->read, NULL)
		|| pthread_mutex_init(data->write, NULL)
		|| pthread_mutex_init(data->ready_lock, NULL))
		return (ft_error("Error: mutex init. failed"));
	return (EXIT_SUCCESS);
}

static int	ft_pthread_create(t_data *data)
{
	int	i;
	t_table	table[MAX_PHILO];

	i = -1;
	init_table(data, &table[0]);
	while (++i < data->n_philo)
	{
		if (pthread_create(&((data->philo)[i])
			, NULL, &philo_routine, (void *) &table[i]))
			return (ft_error("Error: pthread_create failed"));
	}
	data->time_start = ft_gettime();
	pthread_mutex_lock(data->ready_lock);
	data->ready = true;
	pthread_mutex_unlock(data->ready_lock);
	pthread_create(&data->check_routine, NULL, &check_routine, (void *) data);
	return (EXIT_SUCCESS);
}

static int	ft_pthread_join(t_data *data)
{
	int		i;

	i = -1;
	if (pthread_join(data->check_routine, NULL))
		return (ft_error("Error: pthread_join failed"));
	while (++i < data->n_philo)
	{
		if (pthread_join((data->philo)[i], NULL))
		{
			return (ft_error("Error: pthread_join failed"));
		}
	}
	return (EXIT_SUCCESS);
}

int	init_philo(t_data *data)
{
	return (ft_mutex_init(data)
		|| ft_pthread_create(data)
		|| ft_pthread_join(data));
}