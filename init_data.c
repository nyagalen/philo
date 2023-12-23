/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:09:15 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/22 18:17:02 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].meals = 0;
		philos[i].eating = 0;
		philos[i].start_meal = get_time();
		philos[i].left = &forks[i];
		philos[i].right = &forks[(data->nb_philo + i - 1)
			% data->nb_philo];
	}
	data->philos = philos;
}	

void	init_forks(pthread_mutex_t *forks, int ph_num)
{
	int	i;

	i = -1;
	while (++i < ph_num)
		pthread_mutex_init(&forks[i], NULL);
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	if (data->nb_philo == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0
		|| data->nb_philo > 200)
	{
		printf("Invalid arguments\n");
		exit(1);
	}
	if (data->max_meals == 0)
		exit(0);
	data->start_time = get_time();
	data->dead_ph = 0;
	pthread_mutex_init(&data->print_m, NULL);
	pthread_mutex_init(&data->meal_m, NULL);
	pthread_mutex_init(&data->dead_m, NULL);
}
