/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:48:51 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/22 18:07:22 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if ((argc != 6 && argc != 5)
		|| !check_args(argv))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	init_data(&data, argc, argv);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &data, forks);
	activate_threads(philos, forks, data.nb_philo);
	destroy(NULL, &data, forks);
	return (0);
}
