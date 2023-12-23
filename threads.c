/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:34:18 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/22 18:23:52 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *ph)
{
	print(ph, "is thinking");
}

void	zzz(t_philo *ph)
{
	print(ph, "is sleeping");
	ft_usleep(ph->data->time_to_sleep);
}

void	eat(t_philo *ph)
{
	pthread_mutex_lock(ph->right);
	print(ph, "has taken a fork");
	if (ph->data->nb_philo == 1)
	{
		ft_usleep(ph->data->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(ph->left);
	print(ph, "has taken a fork");
	ph->eating = 1;
	print(ph, "is eating");
	pthread_mutex_lock(&ph->data->meal_m);
	ph->start_meal = get_time();
	ph->meals++;
	pthread_mutex_unlock(&ph->data->meal_m);
	ft_usleep(ph->data->time_to_eat);
	ph->eating = 0;
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead(philo->data))
	{
		eat(philo);
		zzz(philo);
		think(philo);
	}
	return (ph);
}

void	activate_threads(t_philo *philos, pthread_mutex_t *forks, int nb_ph)
{
	int			i;
	pthread_t	guard;

	i = -1;
	if (pthread_create(&guard, NULL, &monitor, philos))
		destroy("Failed to create thread", philos->data, forks);
	while (++i < nb_ph)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			destroy("Failed to create thread", philos->data, forks);
	}
	i = -1;
	if (pthread_join(guard, NULL))
		destroy("Thread join error", philos->data, forks);
	while (++i < nb_ph)
	{
		if (pthread_join(philos[i].thread, NULL))
			destroy("Thread join error", philos->data, forks);
	}
}
