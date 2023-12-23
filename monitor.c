/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:11:45 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/23 02:11:40 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_m);
	if (data->dead_ph == 1)
	{
		pthread_mutex_unlock(&data->dead_m);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_m);
	return (0);
}

int	rip(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_m);
	if (get_time() - philo->start_meal >= philo->data->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(&philo->data->meal_m), 1);
	pthread_mutex_unlock(&philo->data->meal_m);
	return (0);
}

int	dead_detected(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].data->nb_philo)
	{
		if (rip(&philos[i]))
		{
			print(&philos[i], "died");
			pthread_mutex_lock(&philos[0].data->dead_m);
			philos[0].data->dead_ph = 1;
			pthread_mutex_unlock(&philos[0].data->dead_m);
			return (1);
		}
	}
	return (0);
}

int	all_ate(t_philo *philos)
{
	int	i;
	int	ph_eaten;

	i = -1;
	ph_eaten = 0;
	if (philos[0].data->max_meals == -1)
		return (0);
	while (++i < philos[0].data->nb_philo)
	{
		pthread_mutex_lock(&philos[0].data->meal_m);
		if (philos[i].meals >= philos[0].data->max_meals)
			ph_eaten++;
		pthread_mutex_unlock(&philos[0].data->meal_m);
	}
	if (ph_eaten == philos[0].data->nb_philo)
	{
		pthread_mutex_lock(&philos[0].data->dead_m);
		philos[0].data->dead_ph = 1;
		pthread_mutex_unlock(&philos[0].data->dead_m);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = pointer;
	while (1)
	{
		if (dead_detected(philos) || all_ate(philos))
			break ;
	}
	return (pointer);
}
