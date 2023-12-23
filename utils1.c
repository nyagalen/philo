/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:54:20 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/23 23:04:18 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(char *str, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			write(2, &str[i], 1);
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->meal_m);
	pthread_mutex_destroy(&data->dead_m);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	print(t_philo *philo, char *str)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_m);
	timestamp = get_time() - philo->data->start_time;
	if (!dead(philo->data))
		printf("%lld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_m);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *num)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (num[i])
	{
		result = result * 10 + num[i] - 48;
		i++;
	}
	return (result);
}

long long	ft_atoll(char *num)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (num[i])
		res = res * 10 + num[i++] - 48;
	return (res);
}
